cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(Sandbox)

link_directories(
    ${dawn_BINARY_DIR}/third_party/glfw/src
    ${glm_BINARY_DIR}
)

file(GLOB_RECURSE WGPU_SRC
    "src/*.cpp"
    "src/*.h"
)

add_executable(Sandbox
    ${WGPU_SRC}
)

target_include_directories(Sandbox
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${glm_SOURCE_DIR}
    PUBLIC ${dawn_SOURCE_DIR}/third_party/glfw/include
    PUBLIC ${dawn_SOURCE_DIR}/include
    PUBLIC ${dawn_BINARY_DIR}/gen/include
)

if(EMSCRIPTEN)
    set_target_properties(Sandbox PROPERTIES SUFFIX ".html")
    target_link_options(Sandbox PRIVATE "-sUSE_WEBGPU=1")
    target_link_options(Sandbox PRIVATE "-sUSE_GLFW=3")
else()
    target_link_libraries(Sandbox
        PRIVATE glfw
        PRIVATE dawncpp
        PRIVATE webgpu_cpp
        PRIVATE webgpu_dawn
        PRIVATE webgpu_glfw
    )

    add_custom_command(TARGET Sandbox
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -DSOURCE_DIR=${CMAKE_SOURCE_DIR} -DBINARY_DIR=${CMAKE_BINARY_DIR} -DDLL_OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR} -P ${CMAKE_SOURCE_DIR}/CopyDLL.cmake 
                   COMMENT "Copying DLL files to binary directory"
    )
endif()