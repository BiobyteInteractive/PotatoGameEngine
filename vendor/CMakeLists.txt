cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include(FetchContent)
include(ExternalProject)

FetchContent_Declare(
  efsw
  GIT_REPOSITORY https://github.com/SpartanJ/efsw.git
)
FetchContent_MakeAvailable(efsw)

FetchContent_Declare(
  toml11
  GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
)
FetchContent_MakeAvailable(toml11)

FetchContent_Declare(
  enet
  GIT_REPOSITORY https://github.com/lsalzman/enet.git
)
FetchContent_MakeAvailable(enet)

FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
)
FetchContent_MakeAvailable(flecs)

fetchcontent_declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
)
fetchcontent_makeavailable(glm)

fetchcontent_declare(
  assimp
  GIT_REPOSITORY https://github.com/assimp/assimp.git
)
fetchcontent_makeavailable(assimp)

fetchcontent_declare(
  nanosvg
  GIT_REPOSITORY https://github.com/memononen/nanosvg.git
)
FetchContent_Populate(nanosvg)

fetchcontent_declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
)
fetchcontent_makeavailable(stb)

FetchContent_Declare(dawn
DOWNLOAD_COMMAND
    cd ${FETCHCONTENT_BASE_DIR}/dawn-src &&
    git init &&
    git fetch --depth=1 https://dawn.googlesource.com/dawn main &&
    git reset --hard FETCH_HEAD
    GIT_PROGRESS TRUE
)

if(EMSCRIPTEN)
    set_target_properties(triangle PROPERTIES SUFFIX ".html")
    target_link_options(triangle PRIVATE "-sUSE_WEBGPU=1")
    target_link_options(triangle PRIVATE "-sUSE_GLFW=3")
else()
    # -- Dawn ---------------------------------------------------------------------
    if (NOT dawn_POPULATED)
        set(DAWN_FETCH_DEPENDENCIES ON)

        if (APPLE)
            set(USE_D3D12 OFF)
            set(USE_VULKAN OFF)
            set(USE_METAL ON)
        else()
            set(USE_D3D12 OFF)
            set(USE_VULKAN ON)
            set(USE_METAL OFF)
        endif()

        set(DAWN_ENABLE_D3D11 OFF)
        set(DAWN_ENABLE_D3D12 ${USE_D3D12})
        set(DAWN_ENABLE_METAL ${USE_METAL})
        set(DAWN_ENABLE_NULL OFF)
        set(DAWN_ENABLE_DESKTOP_GL OFF)
        set(DAWN_ENABLE_OPENGLES OFF)
        set(DAWN_ENABLE_VULKAN ${USE_VULKAN})
        set(TINT_BUILD_SPV_READER OFF)

        # Disable unneeded parts
        set(DAWN_BUILD_SAMPLES OFF)
        set(TINT_BUILD_TINT OFF)
        set(TINT_BUILD_SAMPLES OFF)
        set(TINT_BUILD_DOCS OFF)
        set(TINT_BUILD_TESTS OFF)
        set(TINT_BUILD_FUZZERS OFF)
        set(TINT_BUILD_SPIRV_TOOLS_FUZZER OFF)
        set(TINT_BUILD_AST_FUZZER OFF)
        set(TINT_BUILD_REGEX_FUZZER OFF)
        set(TINT_BUILD_BENCHMARKS OFF)
        set(TINT_BUILD_TESTS OFF)
        set(TINT_BUILD_AS_OTHER_OS OFF)
        set(TINT_BUILD_REMOTE_COMPILE OFF)

        fetchcontent_populate(dawn)
        message(STATUS "Fetching Dawn")
        message(STATUS "  - dawn_source_dir: ${dawn_SOURCE_DIR}")
        message(STATUS "  - dawn_binary_dir: ${dawn_BINARY_DIR}")
        add_subdirectory(${dawn_SOURCE_DIR} ${dawn_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif()
endif()

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG        origin/docking
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/imgui
)

FetchContent_Populate(imgui)

# Create a custom CMakeLists.txt for imgui
file(WRITE ${CMAKE_SOURCE_DIR}/vendor/imgui/CMakeLists.txt [[
cmake_minimum_required(VERSION 3.11)
project(imgui)

link_directories(
    "${dawn_BINARY_DIR}/third_party/glfw/src"
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

add_dependencies(imgui glfw)

target_include_directories(imgui 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${dawn_SOURCE_DIR}/third_party/glfw/include
    PUBLIC ${dawn_SOURCE_DIR}/include
    PUBLIC ${dawn_BINARY_DIR}/gen/include
)

target_link_libraries(imgui
    PUBLIC glfw3dll
)
]])

add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/imgui)
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/finch)

set_target_properties(uninstall                           PROPERTIES FOLDER "Dependencies/GLFW3")
set_target_properties(update_mappings                     PROPERTIES FOLDER "Dependencies/GLFW3")
set_target_properties(assimp                              PROPERTIES FOLDER "Dependencies")
set_target_properties(efsw                                PROPERTIES FOLDER "Dependencies/efsw")
set_target_properties(efsw-static                         PROPERTIES FOLDER "Dependencies/efsw")
set_target_properties(enet                                PROPERTIES FOLDER "Dependencies")
set_target_properties(finch                               PROPERTIES FOLDER "Dependencies")
set_target_properties(flecs                               PROPERTIES FOLDER "Dependencies/flecs")
set_target_properties(flecs_static                        PROPERTIES FOLDER "Dependencies/flecs")
set_target_properties(glm                                 PROPERTIES FOLDER "Dependencies")
set_target_properties(imgui                               PROPERTIES FOLDER "Dependencies")
set_target_properties(unit                                PROPERTIES FOLDER "Dependencies")
set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER "Dependencies")
set_target_properties(zlibstatic                          PROPERTIES FOLDER "Dependencies")