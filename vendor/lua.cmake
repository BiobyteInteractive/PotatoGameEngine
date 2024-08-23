cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  lua
  GIT_REPOSITORY https://github.com/lua/lua.git
  GIT_TAG        origin/master
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/lua
)

FetchContent_Populate(lua)

# Create a custom CMakeLists.txt for lua
file(WRITE ${lua_SOURCE_DIR}/CMakeLists.txt [[
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

file(GLOB_RECURSE LUA_SRC
    "*.c"
    "*.h"
)

add_library(lua STATIC ${LUA_SRC})

target_include_directories(lua
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
]])

add_subdirectory(${lua_SOURCE_DIR})