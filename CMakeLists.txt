cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(ProjectName "Paragon Game Engine")
project(${ProjectName})

include(FetchContent)
include(ExternalProject)

FetchContent_Declare(
  efsw
  GIT_REPOSITORY https://github.com/SpartanJ/efsw.git
)
FetchContent_MakeAvailable(efsw)

FetchContent_Declare(
  toml11
  GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
)
FetchContent_MakeAvailable(toml11)

FetchContent_Declare(
  enet
  GIT_REPOSITORY https://github.com/lsalzman/enet.git
)
FetchContent_MakeAvailable(enet)

FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
)
FetchContent_MakeAvailable(flecs)

fetchcontent_declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
)
fetchcontent_makeavailable(glm)

fetchcontent_declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  SOURCE_SUBDIR "cmake"
)
fetchcontent_makeavailable(glad)

fetchcontent_declare(
  glfw3
  GIT_REPOSITORY https://github.com/glfw/glfw.git
)
fetchcontent_makeavailable(glfw3)

add_subdirectory("engine")
add_subdirectory("sandbox")
add_subdirectory("editor")