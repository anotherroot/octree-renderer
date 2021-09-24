cmake_minimum_required(VERSION 3.17)

# Add Window library
# Build glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)
# add_compile_definitions(GLFW_INCLUDE_NONE IMGUI_IMPL_OPENGL_LOADER_GLAD)

add_subdirectory(glad)


add_library(imgui OBJECT)

target_sources(imgui
  PUBLIC
  imgui/imgui_draw.cpp
  imgui/imgui_widgets.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_demo.cpp
  imgui/imgui.cpp
  imgui/backends/imgui_impl_glfw.cpp
  imgui/backends/imgui_impl_opengl3.cpp
  )
target_include_directories(imgui PUBLIC imgui imgui/backends glfw/include)

