cmake_minimum_required(VERSION 3.10)

set(ProjectName "engine")

project(${ProjectName})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
    set (VCPKG_INSTALL_DIR "${CMAKE_SOURCE_DIR}/vendor/vcpkg/installed/x64-windows")
else ()
    set (VCPKG_INSTALL_DIR "${CMAKE_SOURCE_DIR}/vendor/vcpkg/installed/x64-linux")
endif()

link_directories(
    ${VCPKG_INSTALL_DIR}/lib
)

file(GLOB_RECURSE SPELLBOUND_SRC
    "src/*.cpp"
    "src/*.h"
)

add_library(${ProjectName} INTERFACE)

target_link_libraries(${ProjectName} 
    INTERFACE raylib
    INTERFACE lua
)

if (WIN32)
    file(GLOB_RECURSE vcpkg_dll
        "${CMAKE_SOURCE_DIR}/vendor/vcpkg/installed/x64-windows/bin/*.dll"
    )

    foreach(dll ${vcpkg_dll})
        get_filename_component(filename ${dll} NAME)
        configure_file(${dll} "${CMAKE_SOURCE_DIR}/build/${filename}" COPYONLY)
    endforeach()
endif()