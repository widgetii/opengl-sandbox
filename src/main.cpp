#include <iostream>

#define GL_SILENCE_DEPRECATION 1
#include "glad/glad.h"

#include <GLFW/glfw3.h>

#include "TriangleMesh.hpp"
#include "utils.hpp"

int main() {
  if (!glfwInit()) {
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(640, 480, "Hello world", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Couldn't load OpenGL\n";
    glfwTerminate();
    return -1;
  }

  auto shader = make_shader("shaders/s.vert", "shaders/s.frag");
  TriangleMesh triange;

  glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader);

    triange.draw();

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glDeleteProgram(shader);
  glfwTerminate();
}
