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
		SimpleDraw::Initialize(AppConfig::DebugDrawLimit);
		DebugUI::StaticInitialize(window.wnd, false, true);
		TextureManager::StaticInitialize("../../Assets/Textures/");
		auto input = Input::InputSystem::Get();

		mCurrentState->Initialize();

		isRunning = true;
		while (isRunning)
		{
			window.ProcessMessage();
			input->Update();

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
			}

			
			gs->BeginRender();
			mCurrentState->Render();
			DebugUI::BeginRender();
			mCurrentState->DebugUI();
			DebugUI::EndRender();
			gs->EndRender();
			
		}
		mCurrentState->Terminate();

		TextureManager::StaticTerminate();
		SimpleDraw::Terminate();
		DebugUI::StaticTerminate();
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
