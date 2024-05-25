#! /bin/bash
cd ..
git submodule update --init --recursive
export VCPKG_DEFAULT_TRIPLET="x64-linux"
./vendor/vcpkg/bootstrap-vcpkg.sh -disableMetrics

./vendor/vcpkg/vcpkg install raylib
./vendor/vcpkg/vcpkg install flecs
./vendor/vcpkg/vcpkg install enet
./vendor/vcpkg/vcpkg install box2d
./vendor/vcpkg/vcpkg install lua
./vendor/vcpkg/vcpkg install toml11

mkdir ./build
cd ./build
cmake .. -G Ninja