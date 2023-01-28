#include <../NEngine/Inc/NEngine.h>

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
	NEng::App::AppConfig::AppName = L"HelloWindow";
    NEng::App::AddState
	NEng::App::Run();
    return 0;
}