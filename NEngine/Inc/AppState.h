#pragma once

namespace NEng
{
    class AppState
    {
    private:
        int temp = 0;
    public:
        virtual ~AppState() = default;
        virtual void Initialize() {}
        virtual void Terminate() {}
        virtual void Update(float deltaTime) {}
        virtual void Render() {}
        virtual void DebugUI() {}
    };
}