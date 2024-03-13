#include <GLFW/glfw3.h>

#define GL_SILENCE_DEPRECATION 1
#include <OpenGL/OpenGL.h>

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

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();
}
