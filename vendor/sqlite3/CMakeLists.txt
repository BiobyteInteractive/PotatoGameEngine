PROJECT(sqlite3)
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include_directories(${CMAKE_SOURCE_DIR}/src)
add_library(sqlite3 STATIC sqlite3.c sqlite3.h sqlite3ext.h)

add_definitions(-DSQLITE_ENABLE_RTREE)
add_definitions(-DSQLITE_ENABLE_FTS4)
add_definitions(-DSQLITE_ENABLE_FTS5)
add_definitions(-DSQLITE_ENABLE_JSON1)
add_definitions(-DSQLITE_ENABLE_RBU)
add_definitions(-DSQLITE_ENABLE_STAT4)

#if(WIN32)
#  #add_custom_command(TARGET sqlite POST_BUILD
#  #  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sqlite> ${CMAKE_BINARY_DIR}/sqlite3.exe
#  #  DEPENDS sqlite
#  #)
#  #install(FILES sqlite3.exe DESTINATION bin)
#else()
#  include(FindThreads)
#  target_link_libraries(sqlite m ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
#  install(TARGETS sqlite RUNTIME DESTINATION bin)
#endif()