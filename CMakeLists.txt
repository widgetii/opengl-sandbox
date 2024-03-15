cmake_minimum_required(VERSION 3.1...3.28)

project(
  osandbox
  VERSION 1.0
  LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

# TODO: GL_SILENCE_DEPRECATION for MacOS

# the `pkg_check_modules` function is created with this call
find_package(PkgConfig REQUIRED)

find_package(OpenGL REQUIRED)
# this calls create special `PkgConfig::GLFW3` variables
pkg_check_modules(GLFW3 REQUIRED IMPORTED_TARGET glfw3)

add_subdirectory(glad)

set(HEADERS include/utils.hpp)
set(SRC src/main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    OpenGL::GL
    PkgConfig::GLFW3
    )

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(
    CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} -Werror -fsanitize=undefined -fsanitize=address"
  )
  target_link_options(${PROJECT_NAME}
    BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address
  )
endif()
