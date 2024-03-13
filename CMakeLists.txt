cmake_minimum_required(VERSION 3.1...3.28)

project(
  osandbox
  VERSION 1.0
  LANGUAGES CXX)

# TODO: GL_SILENCE_DEPRECATION for MacOS

# the `pkg_check_modules` function is created with this call
find_package(PkgConfig REQUIRED)

find_package(OpenGL REQUIRED)
# this calls create special `PkgConfig::GLFW3` variables
pkg_check_modules(GLFW3 REQUIRED IMPORTED_TARGET glfw3)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    PkgConfig::GLFW3
    )
