cmake_minimum_required(VERSION 3.11)

project(PotatoGameEngine)

include(FetchContent)
FetchContent_Declare(
  efsw
  GIT_REPOSITORY https://github.com/SpartanJ/efsw.git
)
FetchContent_MakeAvailable(efsw)

add_subdirectory("engine")
add_subdirectory("sandbox")
add_subdirectory("editor")