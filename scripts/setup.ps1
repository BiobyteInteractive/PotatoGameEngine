cd ..;
git submodule update --init --recursive;
$Env:VCPKG_DEFAULT_TRIPLET = "x64-windows";
.\vendor\vcpkg\bootstrap-vcpkg.bat -disableMetrics;

# Scripting
.\vendor\vcpkg\vcpkg.exe install toml11;
.\vendor\vcpkg\vcpkg.exe install lua;

# Networking
.\vendor\vcpkg\vcpkg.exe install entt;

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

# Misc
.\vendor\vcpkg\vcpkg.exe install sqlite3;

# Editor
.\vendor\vcpkg\vcpkg.exe install imgui;
.\vendor\vcpkg\vcpkg.exe install --recurse imgui[docking-experimental];
.\vendor\vcpkg\vcpkg.exe install --recurse imgui[opengl3-binding];
.\vendor\vcpkg\vcpkg.exe install --recurse imgui[glfw-binding];


$directoryPath = ".\build"
if(-not (Test-Path $directoryPath)) {
    New-Item -ItemType Directory -Path $directoryPath
}

cd .\build;
cmake .. -G Ninja;