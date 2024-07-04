cmake_minimum_required(VERSION 3.10)

set(ProjectName "Editor")

project(${ProjectName})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
    set (VCPKG_INSTALL_DIR "${CMAKE_SOURCE_DIR}/vendor/vcpkg/installed/x64-windows")
else()
    set (VCPKG_INSTALL_DIR "${CMAKE_SOURCE_DIR}/vendor/vcpkg/installed/x64-linux")
endif()

link_directories(
    ${VCPKG_INSTALL_DIR}/lib
    ${CMAKE_SOURCE_DIR}/vendor/lib
    ${CMAKE_SOURCE_DIR}/build/editor
)

file(GLOB_RECURSE EDITOR_SRC
    "src/*.cpp"
    "src/*.h"
)

add_executable(${ProjectName} ${EDITOR_SRC})

target_include_directories( ${ProjectName}
    PUBLIC ${VCPKG_INSTALL_DIR}/include
    PUBLIC ${CMAKE_SOURCE_DIR}/engine/src
    PUBLIC ${efsw_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/vendor/include
)

target_link_libraries(${ProjectName}
    PUBLIC engine
    PUBLIC imgui
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

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Assets")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Themes" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Themes")