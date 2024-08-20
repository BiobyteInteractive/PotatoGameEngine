cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  luajit
  GIT_REPOSITORY https://github.com/LuaJIT/LuaJIT.git
  GIT_TAG        origin/v2.1
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/luajit
)

FetchContent_Populate(luajit)

file(COPY ${CMAKE_SOURCE_DIR}/vendor/luajit_src/cmake DESTINATION ${luajit_SOURCE_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/vendor/luajit_src/src/host/cmake DESTINATION ${luajit_SOURCE_DIR}/src/host)

file(COPY ${CMAKE_SOURCE_DIR}/vendor/luajit_src/CMakeLists.txt DESTINATION ${luajit_SOURCE_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/vendor/luajit_src/src/CMakeLists.txt DESTINATION ${luajit_SOURCE_DIR}/src)

set(CMAKE_DEBUG_POSTFIX "")
add_subdirectory(${luajit_SOURCE_DIR})