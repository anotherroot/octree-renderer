cmake_minimum_required(VERSION 3.17)


add_library(window STATIC)

target_include_directories(window PUBLIC include)

target_sources(window
  PRIVATE
  src/win.cpp
  )
target_link_libraries(window PUBLIC glfw glad imgui)
