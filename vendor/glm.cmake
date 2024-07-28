cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(FetchContent)

fetchcontent_declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
)
fetchcontent_makeavailable(glm)