#pragma once

#include "Texture.h"

namespace NEng
{
	using TextureID = size_t;

	class TextureManager final
	{
	public:
		static void StaticInitialize(const std::filesystem::path& root);
		static void StaticTerminate();

		static TextureManager* Get();

		TextureManager() = default;
		~TextureManager();

		TextureManager(const TextureManager& t) = delete;
		TextureManager(const TextureManager&& t) = delete;
		TextureManager& operator=(const TextureManager& t) = delete;
		TextureManager& operator=(const TextureManager&& t) = delete;

		TextureID LoadTexture(const std::filesystem::path& filename, bool useRootDir = true);
		
		void BindVS(TextureID id, uint32_t slot) const;
		void BindPS(TextureID id, uint32_t slot) const;

		void SetRootDirectory(const std::filesystem::path& root);
	private:
		using Inventory = unordered_map<TextureID, std::unique_ptr<Texture>>;

		Inventory inventory;
		std::filesystem::path rootDirectory;

	};
}
