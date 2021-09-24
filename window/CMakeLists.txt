cmake_minimum_required(VERSION 3.17)


add_library(window STATIC)


target_sources(window
  PRIVATE
  src/win.cpp
  )
target_link_libraries(window PUBLIC glfw glad imgui)
target_include_directories(window PUBLIC include ${glfw_SOURCE_DIR} ${glad_SOURCE_DIR} ${imgui_SOURCE_DIR})
