cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(ProjectName "glad")
project(${ProjectName})

add_library(${ProjectName} STATIC "src/glad.c")

target_include_directories( ${ProjectName}
    PUBLIC ${glad_SOURCE_DIR}/include
)