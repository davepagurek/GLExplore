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
#include "third_party/PerlinNoise/PerlinNoise.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Scene &scene);

const float screenWidth = 800;
const float screenHeight = 600;

std::vector<float> genGround(int depth, int octaves) {
  siv::PerlinNoise noise(std::time(nullptr));
  std::vector<std::vector<float>> heights;
  std::vector<float> vertices;
  for (int i = 0; i < depth; i++) {
    heights.push_back(std::vector<float>());
    for (int j = 0; j < depth; j++) {
      float height = noise.octaveNoise0_1(((float)i)/((float)depth-1.0), ((float)j)/((float)depth-1.0), octaves) - 0.5;
      heights[heights.size()-1].push_back(height);
    }
  }

  for (int i = 0; i < heights.size()-1; i++) {
    for (int j = 0; j < heights[i].size()-1; j++) {
      float x1 = -0.5 + ((float)i)*(1.0/((float)depth-1.0));
      float z1 = -0.5 + ((float)j)*(1.0/((float)depth-1.0));
      float y1 = heights[i][j];

      float x2 = -0.5 + ((float)(i+1))*(1.0/((float)depth-1.0));
      float z2 = -0.5 + ((float)j)*(1.0/((float)depth-1.0));
      float y2 = heights[i+1][j];

      float x3 = -0.5 + ((float)i)*(1.0/((float)depth-1.0));
      float z3 = -0.5 + ((float)(j+1))*(1.0/((float)depth-1.0));
      float y3 = heights[i][j+1];

      float x4 = -0.5 + ((float)(i+1))*(1.0/((float)depth-1.0));
      float z4 = -0.5 + ((float)(j+1))*(1.0/((float)depth-1.0));
      float y4 = heights[i+1][j+1];

      // Triangle 1
      vertices.push_back(x1);
      vertices.push_back(y1);
      vertices.push_back(z1);

      vertices.push_back(x2);
      vertices.push_back(y2);
      vertices.push_back(z2);

      vertices.push_back(x3);
      vertices.push_back(y3);
      vertices.push_back(z3);

      // Triangle 2
      vertices.push_back(x4);
      vertices.push_back(y4);
      vertices.push_back(z4);

      vertices.push_back(x3);
      vertices.push_back(y3);
      vertices.push_back(z3);

      vertices.push_back(x2);
      vertices.push_back(y2);
      vertices.push_back(z2);
    }
  }

  return addNormals(vertices);
}

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
    /*
    Lambertian rect(Color(0xFFFFFF), {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    }, &lambertianShader);
    */
    Lambertian rect(Color(0xFFFFFF), addNormals({
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    }), &lambertianShader);
    rect.setTranslation(glm::vec3(-0.5, 0, 0));

    Lambertian redRect = rect;
    redRect.setScale(glm::vec3(0.5, 0.5, 0.5));
    redRect.setTranslation(glm::vec3(1.0, 0.5, -0.5));
    redRect.diffuse = Color(0xFF8888); // Red

    Lambertian ground(Color(0x6EB56E), genGround(40, 3), &lambertianShader); // Green
    ground.setScale(glm::vec3(20, 20, 5));
    ground.setTranslation(glm::vec3(0, -4, -3));

    Scene scene(
      glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f),
      glm::vec3(0.0f, 0.0f, 10.0f),
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
      redRect.setRotation(glm::vec3(time, time, 0));

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      lambertianShader.useProgram();
      rect.draw(scene);
      redRect.draw(scene);
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
