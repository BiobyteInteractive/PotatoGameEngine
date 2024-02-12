$Env:VCPKG_DEFAULT_TRIPLET = "x64-windows"
.\vendor\vcpkg\bootstrap-vcpkg.bat -disableMetrics;

.\vendor\vcpkg\vcpkg.exe install glfw3;
.\vendor\vcpkg\vcpkg.exe install bgfx;
.\vendor\vcpkg\vcpkg.exe install miniaudio;
.\vendor\vcpkg\vcpkg.exe install joltphysics;
.\vendor\vcpkg\vcpkg.exe install entt;
.\vendor\vcpkg\vcpkg.exe install lua;

.\vendor\windows\premake5\premake5.exe vs2022;
