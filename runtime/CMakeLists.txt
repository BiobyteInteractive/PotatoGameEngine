cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(Runtime)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_DEBUG_POSTFIX "")

link_directories(
    ${engine_BINARY_DIR}
)

file(GLOB_RECURSE WGPU_SRC
    "src/*.cpp"
    "src/*.h"
)

add_executable(Runtime
    ${WGPU_SRC}
)

add_dependencies(Runtime engine)

target_include_directories( Runtime
    PUBLIC ${luajit_BINARY_DIR}/src
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

    PUBLIC ${engine_SOURCE_DIR}/src
)
if(EMSCRIPTEN)
    set_target_properties(Runtime PROPERTIES SUFFIX ".html")
    target_link_options(Runtime PRIVATE "-sUSE_WEBGPU=1")
    target_link_options(Runtime PRIVATE "-sUSE_GLFW=3")
else()
    target_link_libraries(Runtime
        PRIVATE engine
    )

    add_custom_command(TARGET Runtime
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -DSOURCE_DIR=${CMAKE_SOURCE_DIR} -DBINARY_DIR=${CMAKE_BINARY_DIR} -DDLL_OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR} -P ${CMAKE_SOURCE_DIR}/CopyDLL.cmake 
                   COMMENT "Copying DLL files to binary directory"
    )
endif()