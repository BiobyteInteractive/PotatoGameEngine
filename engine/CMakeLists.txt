cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(ProjectName "engine")
project(${ProjectName})

link_directories(
    ${CMAKE_SOURCE_DIR}/vendor/luajit
    ${enet_BINARY_DIR}
    ${flecs_BINARY_DIR}
    ${glm_BINARY_DIR}
    ${imgui_BINARY_DIR}
    ${efsw_BINARY_DIR}
    ${dawn_BINARY_DIR}/third_party/glfw/src
    ${finch_BINARY_DIR}
    ${sqlite3_BINARY_DIR}
)

file(GLOB_RECURSE ENGINE_SRC
    "src/*.cpp"
    "src/*.h"
)

add_library(${ProjectName} SHARED ${ENGINE_SRC})
add_dependencies(${ProjectName} enet flecs glm glfw imgui efsw)

target_include_directories( ${ProjectName}
    PUBLIC ${CMAKE_SOURCE_DIR}/vendor/luajit
    PUBLIC ${efsw_SOURCE_DIR}/include
    PUBLIC ${enet_SOURCE_DIR}/include
    PUBLIC ${flecs_SOURCE_DIR}/include
    PUBLIC ${glm_SOURCE_DIR}
    PUBLIC ${toml11_SOURCE_DIR}
    PUBLIC ${imgui_SOURCE_DIR}
    PUBLIC ${imgui_SOURCE_DIR}/backends
    PUBLIC ${finch_SOURCE_DIR}/src/include

    PUBLIC ${dawn_SOURCE_DIR}/third_party/glfw/include
    PUBLIC ${dawn_SOURCE_DIR}/include
    PUBLIC ${dawn_BINARY_DIR}/gen/include

    PUBLIC ${sqlite3_SOURCE_DIR}
)

target_link_libraries(${ProjectName}
    PUBLIC lua51
    PUBLIC luajit
    PUBLIC minilua
    PUBLIC glfw
    PUBLIC dawncpp
    PUBLIC webgpu_cpp
    PUBLIC webgpu_dawn
    PUBLIC webgpu_glfw
    PUBLIC efsw
    PUBLIC imgui
    PUBLIC sqlite3
)