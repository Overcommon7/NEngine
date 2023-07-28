#include "Precompiled.h"
#include "TextureManager.h"

namespace
{
	std::unique_ptr<NEng::TextureManager> instance;
}

void NEng::TextureManager::StaticInitialize(const std::filesystem::path& root)
{
	instance = std::make_unique<TextureManager>();
	instance->SetRootDirectory(root);
}

void NEng::TextureManager::StaticTerminate()
{
	for (auto& [id, texture] : instance->inventory)
		texture->Terminate();
	instance.reset();
}

NEng::TextureManager* NEng::TextureManager::Get()
{
	return instance.get();
}

NEng::TextureManager::~TextureManager()
{

}

NEng::TextureID NEng::TextureManager::LoadTexture(const std::filesystem::path& filename, bool useRootDir)
{
	auto textureID = std::filesystem::hash_value(filename);
	auto [iter, success] = inventory.insert({ textureID, nullptr });
	if (success)
	{
		auto& texturePtr = iter->second;
		texturePtr = std::make_unique<Texture>();
		texturePtr->Initialize(useRootDir ? rootDirectory / filename : filename);
	}
	return textureID;
}

void NEng::TextureManager::BindVS(TextureID id, uint32_t slot) const
{
	if (id == 0) return;

	auto iter = inventory.find(id);
	if (iter != inventory.end()) iter->second->BindVS(slot);
}

void NEng::TextureManager::BindPS(TextureID id, uint32_t slot) const
{
	if (id == 0) return;

	auto iter = inventory.find(id);
	if (iter != inventory.end()) iter->second->BindPS(slot);
}

void NEng::TextureManager::SetRootDirectory(const std::filesystem::path& root)
{
	rootDirectory = root;
}
