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
		auto graphicsSystem = GraphicsSystem::	
		isRunning = true;
		while (isRunning)
		{
			window.PrrocessMessage();
			if (!window.isActive || Input::InputSystem::Get()->IsKeyPressed(closeKey))
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
			auto deltaTime = TimeUtil::GetDeltaTime();
			if (deltaTime < 0.5f)
			{
				mCurrentState->Update(deltaTime);
			}

			mCurrentState->Render();
			mCurrentState->DebugUI();
			
		}
		mCurrentState->Terminate();
		Input::InputSystem::StaticTerminate();
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
