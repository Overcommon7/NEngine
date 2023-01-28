#pragma once

namespace NEng
{
    class AppState;

    class App final
    {
    private:
        using AppStateMap = std::map<std::string, std::unique_ptr<AppState>>;

        inline static AppStateMap mAppStates = {};
        inline static AppState* mCurrentState = nullptr;
        inline static AppState* mNextState = nullptr;

        static inline bool isRunning = false;
    public:
        struct AppConfig
        {
            inline static std::wstring AppName = L"AppName";
            inline static uint32_t WinWidth = 1280;
            inline static uint32_t WinHeight = 720;
        };

        App() = delete;
        App(const App& a) = delete;
        App& operator=(const App& a) = delete;

        
        static inline float deltaTime = {};
        static inline Input::KeyCode closeKey = Input::KeyCode::ESCAPE;
        static void Run();
        static void Quit();
        static void ChangeState(const std::string& stateName);
        template<class StateType>
        inline static void AddState(const std::string& stateName)
        {
            static_assert(std::is_base_of_v<AppState, StateType>, "AddState must be of type AppState");

            auto [iter, success] = mAppStates.try_emplace(stateName, nullptr);
            if (success)
            {
                auto& ptr = iter->second;
                ptr = std::make_unique<StateType>();
                if (mCurrentState == nullptr)
                {
                    mCurrentState = ptr.get();
                }
            }
        }
    };

}
