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

const float screenWidth = 800;
const float screenHeight = 600;

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // required for osx

  GLFWwindow* window = glfwCreateWindow((int)screenWidth, (int)screenHeight, "Test", NULL, NULL);
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
    //front
    0.5f,  0.5f, -0.5f,  // top right
    0.5f, -0.5f, -0.5f,  // bottom right
    -0.5f, -0.5f, -0.5f,  // bottom left
    -0.5f,  0.5f, -0.5f,   // top left 

    // back
    0.5f,  0.5f, 0.5f,  // top right
    0.5f, -0.5f, 0.5f,  // bottom right
    -0.5f, -0.5f, 0.5f,  // bottom left
    -0.5f,  0.5f, 0.5f   // top left
  }, {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3,    // second triangle

    4, 5, 7,
    5, 6, 7,

    5, 7, 3,
    5, 1, 3,

    4, 0, 2,
    4, 6, 2,
    
    2, 3, 6,
    6, 3, 7,

    0, 1, 5,
    0, 4, 5
  });

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);
  glm::mat4 view = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -3.0f)); 

  while(!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    rect.draw(projection, view);

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
