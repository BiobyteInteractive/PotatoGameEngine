cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_FOLDER Dependencies)

set(ProjectName "Paragon Game Engine")
project(${ProjectName})

# Download and Setup dependencies
add_subdirectory("vendor")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_FOLDER /)

add_subdirectory("engine")
add_subdirectory("runtime")
add_subdirectory("sandbox")
#IF (WIN32)
#    add_subdirectory("editor")
#    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT editor)
#ENDIF()