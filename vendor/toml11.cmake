cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  toml11
  GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
)
FetchContent_MakeAvailable(toml11)