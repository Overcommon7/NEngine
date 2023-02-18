#include <../NEngine/Inc/NEngine.h>
#include "GameState.h"

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    NEng::App::AppConfig::AppName = L"HelloMeshBuilder";
    NEng::App::AddState<SphereMesh>("SphereMesh");
    NEng::App::AddState<CubeMesh>("CubeMesh");
    NEng::App::AddState<CylinderMesh>("CylinderMesh");
    NEng::App::AddState<PlaneMesh>("PlaneMesh");
    NEng::App::AddState<RectangleMesh>("RectangleMesh");
    NEng::App::Run();
    return 0;
}