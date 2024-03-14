#include <iostream>

#define GL_SILENCE_DEPRECATION 1
#include "glad/glad.h"

#include <GLFW/glfw3.h>

int main() {
  if (!glfwInit()) {
    return -1;
  }

  GLFWwindow *window = glfwCreateWindow(640, 480, "Hello world", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Couldn't load OpenGL\n";
    glfwTerminate();
    return -1;
  }

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();
}
