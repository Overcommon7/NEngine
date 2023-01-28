#include <../NEngine/Inc/NEngine.h>
#include "GameState.h"

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    NEng::App::AppConfig::AppName = L"ColorChange";
    NEng::App::AddState<GameState>("GameState");
    NEng::App::Run();
    return 0;
}