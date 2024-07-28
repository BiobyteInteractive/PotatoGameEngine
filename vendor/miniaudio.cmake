cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(FetchContent)

fetchcontent_declare(
  miniaudio
  GIT_REPOSITORY https://github.com/mackron/miniaudio.git
)
FetchContent_Populate(miniaudio)