cd ..;
git submodule update --init --recursive;
$Env:VCPKG_DEFAULT_TRIPLET = "x64-windows";
.\vendor\vcpkg\bootstrap-vcpkg.bat -disableMetrics;

# Scripting
.\vendor\vcpkg\vcpkg.exe install toml11;
.\vendor\vcpkg\vcpkg.exe install lua;

# Networking
.\vendor\vcpkg\vcpkg.exe install enet;

# ECS
.\vendor\vcpkg\vcpkg.exe install flecs;

# Physics
.\vendor\vcpkg\vcpkg.exe install joltphysics;

# Rendering
.\vendor\vcpkg\vcpkg.exe install glm;
.\vendor\vcpkg\vcpkg.exe install glad;
.\vendor\vcpkg\vcpkg.exe install glfw3;

# Audio
.\vendor\vcpkg\vcpkg.exe install miniaudio;

# Editor
.\vendor\vcpkg\vcpkg.exe install imgui;
.\vendor\vcpkg\vcpkg.exe install "imgui[docking-experimental]";
.\vendor\vcpkg\vcpkg.exe install "imgui[opengl3-binding]";


$directoryPath = ".\build"
if(-not (Test-Path $directoryPath)) {
    New-Item -ItemType Directory -Path $directoryPath
}

cd .\build;
cmake .. -G Ninja;