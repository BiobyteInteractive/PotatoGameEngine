cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(ProjectName "Paragon Game Engine")
project(${ProjectName})

# Download and Setup dependencies
add_subdirectory("vendor")

add_subdirectory("engine")
add_subdirectory("sandbox")
add_subdirectory("editor")