#include "GameState.h"

void GameState::Initialize()
{
	NEng::GraphicsSystem::Get()->SetClearColor(Colors::Red);
}

void GameState::Update(float deltaTime)
{
	auto input = NEng::Input::InputSystem::Get();
	auto gs = NEng::GraphicsSystem::Get();

	if (input->IsKeyPressed(NEng::Input::KeyCode::ONE)) gs->SetClearColor(Colors::Black);
	else if (input->IsKeyPressed(NEng::Input::KeyCode::TWO)) gs->SetClearColor(Colors::Red);
	else if (input->IsKeyPressed(NEng::Input::KeyCode::THREE)) gs->SetClearColor(Colors::Green);
	else if (input->IsKeyPressed(NEng::Input::KeyCode::FOUR)) gs->SetClearColor(Colors::Blue);
	else if (input->IsKeyPressed(NEng::Input::KeyCode::FIVE)) gs->SetClearColor(Colors::Yellow);
	else if (input->IsKeyPressed(NEng::Input::KeyCode::SIX)) gs->SetClearColor(Colors::Purple);
}
