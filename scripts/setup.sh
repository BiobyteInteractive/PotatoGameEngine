#! /bin/bash
cd ..
git submodule update --init --recursive
export VCPKG_DEFAULT_TRIPLET="x64-linux"
./vendor/vcpkg/bootstrap-vcpkg.sh -disableMetrics

# Scripting
./vendor/vcpkg/vcpkg install toml11
./vendor/vcpkg/vcpkg install lua

# Networking
./vendor/vcpkg/vcpkg install enet

# ECS
./vendor/vcpkg/vcpkg install flecs

# Physics
./vendor/vcpkg/vcpkg install joltphysics

# Rendering
./vendor/vcpkg/vcpkg install glm
./vendor/vcpkg/vcpkg install glad
./vendor/vcpkg/vcpkg install glfw3

# Audio
./vendor/vcpkg/vcpkg install miniaudio

# Editor
./vendor/vcpkg/vcpkg install imgui
./vendor/vcpkg/vcpkg install imgui[docking-experimental]
./vendor/vcpkg/vcpkg install imgui[opengl3-binding]

mkdir ./build
cd ./build
cmake .. -G Ninja