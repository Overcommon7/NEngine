#include "Precompiled.h"
#include "App.h"
#include "AppState.h"

namespace NEng
{
	void App::Run()
	{
		Window window;
		window.Initialize(
			GetModuleHandle(nullptr),
			AppConfig::AppName,
			AppConfig::WinWidth,
			AppConfig::WinHeight);

		Input::InputSystem::StaticInitialize(window.wnd);
		GraphicsSystem::StaticInitialize(window.wnd, false);
		auto input = Input::InputSystem::Get();
		isRunning = true;
		while (isRunning)
		{
			window.PrrocessMessage();
			if (!window.isActive || input->IsKeyPressed(closeKey))
			{
				Quit();
				break;
			}

			if (mNextState != nullptr)
			{
				mCurrentState->Terminate();
				mCurrentState = std::exchange(mNextState, nullptr);
				mCurrentState->Initialize();
			}

			// run the game
			auto gs = GraphicsSystem::Get();
			auto deltaTime = TimeUtil::GetDeltaTime();
			if (deltaTime < 0.5f)
			{
				mCurrentState->Update(deltaTime);

				if (input->IsKeyPressed(Input::KeyCode::ONE)) gs->SetClearColor(Colors::Black);
				else if (input->IsKeyPressed(Input::KeyCode::TWO)) gs->SetClearColor(Colors::Red);
				else if (input->IsKeyPressed(Input::KeyCode::THREE)) gs->SetClearColor(Colors::Green);
				else if (input->IsKeyPressed(Input::KeyCode::FOUR)) gs->SetClearColor(Colors::Blue);
				else if (input->IsKeyPressed(Input::KeyCode::FIVE)) gs->SetClearColor(Colors::Yellow);
				else if (input->IsKeyPressed(Input::KeyCode::SIX)) gs->SetClearColor(Colors::Purple);
			}

			
			gs->BeginRender();
			mCurrentState->Render();
			mCurrentState->DebugUI();
			gs->EndRender();
			
		}
		mCurrentState->Terminate();
		Input::InputSystem::StaticTerminate();
		GraphicsSystem::StaticTerminate();
		window.Terminate();

	}

	void App::Quit()
	{
		isRunning = false;
	}

	void App::ChangeState(const std::string& stateName)
	{
		auto iter = mAppStates.find(stateName);
		if (iter != mAppStates.end())
		{
			mNextState = iter->second.get();
		}
	}
}
