# CMake taken from https://github.com/walterschell/finch/blob/cmake/CMakeLists.txt

# Need transitive dependencies introduced in 2.8.12
cmake_minimum_required(VERSION 2.8.12)

project(Finch LANGUAGES "C")

set(finch_warning_flags "-Wall" "-Wextra" "-Werror" "-Wno-unused-parameter")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

IF (WIN32)
    ADD_DEFINITIONS (-D_CRT_SECURE_NO_WARNINGS )
ENDIF ()

set(opt_DIR "src/optional")
set(vm_DIR "src/vm")

# TODO: Don't glob
file(GLOB opt_SRCS ${opt_DIR}/*.c)
file(GLOB vm_SRCS ${vm_DIR}/*.c)

set(finch_SRCS ${vm_SRCS} ${opt_SRCS})

add_library(finch STATIC ${finch_SRCS})

target_include_directories(finch PUBLIC src/include PRIVATE src/vm src/optional)

target_link_libraries(finch INTERFACE m)

target_compile_options(finch PRIVATE "-Wall")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(finch PUBLIC -DDEBUG)
endif()


INSTALL (TARGETS finch
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)


IF (NOT DEFINED SKIP_INSTALL_HEADERS)
    INSTALL(
        FILES
            src/include/finch.h
            src/include/finch.hpp
        DESTINATION include
    )
ENDIF ()