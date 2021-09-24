cmake_minimum_required(VERSION 3.17)


project(
  octree
  VERSION "0.1.0"
  DESCRIPTION "Octree traversal renderer"
  LANGUAGES CXX C
  )
set(CMAKE_CXX_STANDARD 17)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(ext)
add_subdirectory(window)

add_executable(desktop)
target_sources(
  desktop
  PRIVATE
  src/main.cpp
  )

target_include_directories(desktop PUBLIC include)
target_link_libraries(desktop PUBLIC window )
