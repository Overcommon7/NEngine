#include <../NEngine/Inc/NEngine.h>
#include "GameState.h"

void Run()
{
    NEng::App::AppConfig::AppName = L"HelloTexture";
    NEng::App::AddState<GameState>("State");
    NEng::App::Run();
}

int main()
{
    Run();
}

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    Run();
    return 0;
}


