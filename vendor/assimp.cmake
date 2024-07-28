cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(FetchContent)

fetchcontent_declare(
  assimp
  GIT_REPOSITORY https://github.com/assimp/assimp.git
)
fetchcontent_makeavailable(assimp)