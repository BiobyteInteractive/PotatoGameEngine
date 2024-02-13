$Env:VCPKG_DEFAULT_TRIPLET = "x64-windows"
.\vendor\vcpkg\bootstrap-vcpkg.bat -disableMetrics;

.\vendor\vcpkg\vcpkg.exe install glfw3;
.\vendor\vcpkg\vcpkg.exe install bgfx;
.\vendor\vcpkg\vcpkg.exe install miniaudio;
.\vendor\vcpkg\vcpkg.exe install joltphysics;
.\vendor\vcpkg\vcpkg.exe install entt;
.\vendor\vcpkg\vcpkg.exe install enet;
.\vendor\vcpkg\vcpkg.exe install lua;

# Downloads the latest version of nuklear straight from their github. (The VCPKG version is outdated)
Invoke-WebRequest -Uri "https://raw.githubusercontent.com/Immediate-Mode-UI/Nuklear/master/nuklear.h" -OutFile (Join-Path ((Get-Location).Path) "vendor\vcpkg\installed\x64-windows\include\nuklear.h") 

# Imgui for the editor
.\vendor\vcpkg\vcpkg.exe install imgui;
.\vendor\vcpkg\vcpkg.exe install imgui[docking-experimental];
.\vendor\vcpkg\vcpkg.exe install imgui[glfw-binding];
.\vendor\vcpkg\vcpkg.exe install imgui-node-editor;

.\vendor\windows\premake5\premake5.exe vs2022;
