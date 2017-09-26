#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <ctime>

#include "Lambertian.hpp"
#include "Color.hpp"
#include "Scene.hpp"
#include "geometry.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Scene &scene);

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
  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);

  try {
    GLShader lambertianShader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");

    Lambertian rect(Color(0xFFFFFF), cube(), &lambertianShader); // White
    rect.setTranslation(glm::vec3(-0.5, 0, 0));

    Lambertian redSphere(Color(0xFF8888), sphere(), &lambertianShader); // Red
    redSphere.setScale(glm::vec3(0.5, 0.5, 0.5));
    redSphere.setTranslation(glm::vec3(1.0, 0.5, -0.5));

    Lambertian ground(Color(0x6EB56E), hills(80, 6), &lambertianShader); // Green
    ground.setScale(glm::vec3(40, 40, 3));
    ground.setTranslation(glm::vec3(0, -4, -3));

    Scene scene(
      glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f),
      glm::vec3(0.0f, 0.0f, 20.0f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      Color(0x888888), // Grey
      {
        {Color(0xFFDD33), glm::vec3(0.5, 0.0, 1.0)}, // Orange
        {Color(0x330066), glm::vec3(-3, 0.0, -2.0)} // Indigo
      }
    );

    while(!glfwWindowShouldClose(window)) {
      processInput(window, scene);

      float time = glfwGetTime();
      rect.setRotation(glm::vec3(0, time, time));
      redSphere.setRotation(glm::vec3(time, time, 0));

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      lambertianShader.useProgram();
      rect.draw(scene);
      redSphere.draw(scene);
      ground.draw(scene);

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  } catch (ShaderProgramCompilationError& e) {
    std::cerr << e.getMessage() << std::endl;
    exit(1);
  }

  glfwTerminate();
  return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, Scene &scene) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  } else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    scene.moveCameraLeft();
  } else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    scene.moveCameraRight();
  } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    scene.moveCameraForward();
  } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    scene.moveCameraBackward();
  }
}
