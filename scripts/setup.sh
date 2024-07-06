#! /bin/bash
cd ..
git submodule update --init --recursive
export VCPKG_DEFAULT_TRIPLET="x64-linux"
./vendor/vcpkg/bootstrap-vcpkg.sh -disableMetrics

# Scripting
./vendor/vcpkg/vcpkg install toml11

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

# Misc
./vendor/vcpkg/vcpkg install sqlite3
./vendor/vcpkg/vcpkg install efsw

# Editor
./vendor/vcpkg/vcpkg install imgui
./vendor/vcpkg/vcpkg install --recurse imgui[docking-experimental]
./vendor/vcpkg/vcpkg install --recurse imgui[opengl3-binding]
./vendor/vcpkg/vcpkg install --recurse imgui[glfw-binding]

mkdir ./build
cd ./build
cmake .. -G Ninja