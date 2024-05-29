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

file(GLOB_RECURSE ENGINE_SRC
    "src/*.cpp"
    "src/*.h"
)

add_library(${ProjectName} SHARED ${ENGINE_SRC})

target_include_directories( ${ProjectName}
    PUBLIC ${VCPKG_INSTALL_DIR}/include
)

target_link_libraries(${ProjectName} 
    PUBLIC glad
    PUBLIC glfw3dll
    PUBLIC sqlite3
    PUBLIC efsw
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

add_custom_command(TARGET ${ProjectName} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                           ${CMAKE_SOURCE_DIR}/build/engine/engine.dll
                           ${CMAKE_SOURCE_DIR}/build/engine.dll
)