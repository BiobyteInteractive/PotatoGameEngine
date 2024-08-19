cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG        origin/docking
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/imgui
)

FetchContent_Populate(imgui)

# Create a custom CMakeLists.txt for imgui
file(WRITE ${CMAKE_SOURCE_DIR}/vendor/imgui/CMakeLists.txt [[
    cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
    project(imgui)

    link_directories(
        ${dawn_BINARY_DIR}/third_party/glfw/src
    )

    file(GLOB_RECURSE IMGUI_SRC
        "imconfig.h"
        "imgui_demo.cpp"
        "imgui_draw.cpp"
        "imgui_internal.h"
        "imgui_tables.cpp"
        "imgui_widgets.cpp"
        "imgui.cpp"
        "imgui.h"
        "imstb_rectpack.h"
        "imstb_textedit.h"
        "imstb_truetype.h"

        "backends/imgui_impl_glfw.cpp"
        "backends/imgui_impl_glfw.h"

        "backends/imgui_impl_wgpu.cpp"
        "backends/imgui_impl_wgpu.h"
    )

    add_library(imgui STATIC ${IMGUI_SRC})

    add_dependencies(imgui glfw dawn_common dawn_glfw dawn_headers dawn_native_objects dawn_platform dawncpp_headers)

    target_include_directories(imgui 
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}

        PUBLIC ${dawn_SOURCE_DIR}/third_party/glfw/include

        PUBLIC ${dawn_SOURCE_DIR}/include
        PUBLIC ${dawn_BINARY_DIR}/gen/include
    )

    target_link_libraries(imgui
        PUBLIC glfw
        PUBLIC dawncpp
        PUBLIC webgpu_cpp
        PUBLIC webgpu_dawn
        PUBLIC webgpu_glfw
    )
]])

add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/imgui)