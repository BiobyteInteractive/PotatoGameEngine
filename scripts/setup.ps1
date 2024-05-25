cd ..;
git submodule update --init --recursive;
$Env:VCPKG_DEFAULT_TRIPLET = "x64-windows";
.\vendor\vcpkg\bootstrap-vcpkg.bat -disableMetrics;

.\vendor\vcpkg\vcpkg.exe install toml11;
.\vendor\vcpkg\vcpkg.exe install lua;   
.\vendor\vcpkg\vcpkg.exe install box2d; 
.\vendor\vcpkg\vcpkg.exe install enet;  
.\vendor\vcpkg\vcpkg.exe install flecs; 
.\vendor\vcpkg\vcpkg.exe install raylib;

$directoryPath = ".\build"
if(-not (Test-Path $directoryPath)) {
    New-Item -ItemType Directory -Path $directoryPath
}

cd .\build;
cmake .. -G Ninja;