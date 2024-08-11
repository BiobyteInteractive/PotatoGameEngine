cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(FetchContent)

include(toml11.cmake)
include(efsw.cmake)

include(glm.cmake)
set(BUILD_SHARED_LIBS OFF)
include(dawn.cmake)
set(BUILD_SHARED_LIBS ON)
include(imgui.cmake)

include(enet.cmake)
include(flecs.cmake)
include(assimp.cmake)
include(stb.cmake)
include(nanosvg.cmake)
include(miniaudio.cmake)

add_subdirectory(finch)