#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include "Lambertian.hpp"
#include "Color.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
std::string slurp(std::string filename);

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // required for osx

  GLFWwindow* window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
  if (!window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  try {
    Lambertian::compileShaderProgram();
  } catch (ShaderProgramCompilationError& e) {
    std::cerr << e.getMessage() << std::endl;
    exit(1);
  }

  Lambertian rect(Color(0xFFFFFFFF), {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
  }, {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
  });

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while(!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    rect.draw();

    glfwSwapBuffers(window);
    glfwPollEvents();    
  }

  Lambertian::cleanup();
  glfwTerminate();
  return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
