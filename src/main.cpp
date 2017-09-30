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
    GLShader lambertianShader("src/shaders/lambertian/vertex.glsl", "src/shaders/lambertian/fragment.glsl");

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
      Color(0xDDDDDD), // Grey
      {
        {Color(0xB59D24), glm::vec3(0.5, 2.0, 10.0)}, // Orange
        {Color(0x330066), glm::vec3(-3, 0.0, -2.0)} // Indigo
      },
      25.0f
    );

    glm::vec3 lightPos = scene.getPointLights()[0].location;

    // Frame buffer
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);

    // Texture
    unsigned int depthCubemap;
    glGenTextures(1, &depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);

    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    for (unsigned int i = 0; i < 6; i++) {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
        SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    GLShader pointShadowShader("src/shaders/pointdepth/vertex.glsl", "src/shaders/pointdepth/fragment.glsl", "src/shaders/pointdepth/geometry.glsl");

    Color sky(0x8AD6FF);

    while(!glfwWindowShouldClose(window)) {
      processInput(window, scene);

      float time = glfwGetTime();
      rect.setRotation(glm::vec3(0, time, time));
      redSphere.setRotation(glm::vec3(time, time, 0));

      // Cubemap transforms
      float nearPlane = 1.0f;
      float farPlane = scene.getFarPlane();
      glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, nearPlane, farPlane);
      std::vector<glm::mat4> shadowTransforms;
      shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
      shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
      shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
      shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
      shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
      shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

      // Render to cubemap
      glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
      glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
      glClear(GL_DEPTH_BUFFER_BIT);
      pointShadowShader.useProgram();
      for (int i = 0; i < 6; i++) {
        unsigned int loc = pointShadowShader.getUniformLocation(("shadowMatrices[" + std::to_string(i) + "]").c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(shadowTransforms[i]));
      }
      glUniform1f(pointShadowShader.getUniformLocation("farPlane"), farPlane);
      glUniform3fv(pointShadowShader.getUniformLocation("lightPos"), 1, glm::value_ptr(lightPos));
      rect.shadow(scene, pointShadowShader);
      redSphere.shadow(scene, pointShadowShader);
      ground.shadow(scene, pointShadowShader);

      // Switch to main shader
      int width, height;
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      glfwGetFramebufferSize(window, &width, &height);
      glViewport(0, 0, width, height);
      glClearColor(sky.r(), sky.g(), sky.b(), 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      lambertianShader.useProgram();
      glUniform1f(lambertianShader.getUniformLocation("farPlane"), farPlane);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);

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
