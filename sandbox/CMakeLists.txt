cmake_minimum_required(VERSION 3.10)

set(ProjectName "sandbox")
project(${ProjectName})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

link_directories(
    ${engine_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/vendor/lib
    ${enet_BINARY_DIR}
    ${flecs_BINARY_DIR}
    ${glm_BINARY_DIR}
    ${imgui_BINARY_DIR}
    ${efsw_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/_deps/glfw3-build/src
)

file(GLOB_RECURSE SANDBOX_SRC
    "src/*.cpp"
    "src/*.h"
)

add_executable(${ProjectName} ${SANDBOX_SRC})

add_dependencies(${ProjectName} engine)

target_include_directories( ${ProjectName}
    PUBLIC ${engine_SOURCE_DIR}/src
    PUBLIC ${CMAKE_SOURCE_DIR}/vendor/include
    PUBLIC ${efsw_SOURCE_DIR}/include
    PUBLIC ${enet_SOURCE_DIR}/include
    PUBLIC ${flecs_SOURCE_DIR}/include
    PUBLIC ${glm_SOURCE_DIR}
    PUBLIC ${toml11_SOURCE_DIR}
    PUBLIC ${imgui_SOURCE_DIR}
    PUBLIC ${imgui_SOURCE_DIR}/backends
    PUBLIC ${glfw_SOURCE_DIR}/include
)

target_link_libraries(${ProjectName}
    PUBLIC engine
)

add_custom_command(TARGET ${ProjectName} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -DSOURCE_DIR=${CMAKE_SOURCE_DIR} -DBINARY_DIR=${CMAKE_BINARY_DIR} -DDLL_OUTPUT_DIR=${sandbox_BINARY_DIR} -P ${CMAKE_SOURCE_DIR}/CopyDLL.cmake 
                   COMMENT "Copying DLL files to binary directory"
)