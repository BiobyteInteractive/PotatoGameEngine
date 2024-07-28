cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  enet
  GIT_REPOSITORY https://github.com/lsalzman/enet.git
)
FetchContent_MakeAvailable(enet)