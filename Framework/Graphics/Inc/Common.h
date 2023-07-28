#pragma once

#include <Core/Inc/Core.h>
#include <Math/Inc/NMath.h>

#include <ImGui/Inc/imgui.h>

#include <d3d11_1.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

template<class T>
inline void SafeRelease(T*& ptr)
{
    if (ptr)
    {
        ptr->Release();
        ptr = nullptr;
    }
}

inline std::exception CreateException(const char* message, const char* file, const int& line)
{
    auto str = string(message) + " - " + file + " - " + to_string(line);
    cout << str;
    return std::exception(str.c_str());
}
