cmake_minimum_required(VERSION 3.10)

set(ProjectName "engine")
project(${ProjectName})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

link_directories(
    ${CMAKE_SOURCE_DIR}/vendor/lib
    ${enet_BINARY_DIR}
    ${flecs_BINARY_DIR}
    ${glm_BINARY_DIR}
    ${imgui_BINARY_DIR}
    ${efsw_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/_deps/glfw3-build/src
    ${finch_BINARY_DIR}
)

file(GLOB_RECURSE ENGINE_SRC
    "src/*.cpp"
    "src/*.h"
)

add_library(${ProjectName} SHARED ${ENGINE_SRC})

add_dependencies(${ProjectName} enet flecs glm glfw imgui efsw)

add_compile_definitions(DLLBuild)

target_include_directories( ${ProjectName}
    PUBLIC ${CMAKE_SOURCE_DIR}/vendor/include
    PUBLIC ${efsw_SOURCE_DIR}/include
    PUBLIC ${enet_SOURCE_DIR}/include
    PUBLIC ${flecs_SOURCE_DIR}/include
    PUBLIC ${glm_SOURCE_DIR}
    PUBLIC ${toml11_SOURCE_DIR}
    PUBLIC ${imgui_SOURCE_DIR}
    PUBLIC ${imgui_SOURCE_DIR}/backends
    PUBLIC ${glfw_SOURCE_DIR}/include
    PUBLIC ${finch_SOURCE_DIR}/src/include
)

target_link_libraries(${ProjectName}
    PUBLIC finch
    PUBLIC glad
    PUBLIC glfw3dll
    PUBLIC sqlite3
    PUBLIC efsw
    PUBLIC imgui
)