cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(FetchContent)

fetchcontent_declare(
  nanosvg
  GIT_REPOSITORY https://github.com/memononen/nanosvg.git
)
FetchContent_Populate(nanosvg)