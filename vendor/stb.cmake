cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(FetchContent)

fetchcontent_declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
)
fetchcontent_makeavailable(stb)