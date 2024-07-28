cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  efsw
  GIT_REPOSITORY https://github.com/SpartanJ/efsw.git
)
FetchContent_MakeAvailable(efsw)