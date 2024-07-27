cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(ProjectName "Paragon Game Engine")
project(${ProjectName})

set(CMAKE_DEBUG_POSTFIX "")

# Download and Setup dependencies
add_subdirectory("vendor")

#add_subdirectory("engine")
#add_subdirectory("sandbox")
IF (WIN32)
    #add_subdirectory("editor")
    #set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT editor)
ENDIF()