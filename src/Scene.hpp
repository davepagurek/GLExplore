#ifndef SCENE_H
#define SCENE_H

#include "Color.hpp"
#include "PointLight.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Scene {
  glm::mat4 projection;
  glm::vec3 cameraPos, cameraTarget;
  glm::mat4 view;

  Color ambientLight;
  std::vector<PointLight> pointLights;

  Scene(glm::mat4 projection, glm::vec3 cameraPos, glm::vec3 cameraTarget, Color ambientLight,
        std::vector<PointLight> pointLights):
    projection(projection),
    cameraPos(cameraPos),
    cameraTarget(cameraTarget),
    view(glm::lookAt(cameraPos, cameraTarget, glm::vec3(0,1,0))),
    ambientLight(ambientLight),
    pointLights(std::move(pointLights)) {}

  void moveCameraLeft() {
    cameraPos.x += 0.05;
    cameraTarget.x += 0.05;
    view = glm::lookAt(cameraPos, cameraTarget, glm::vec3(0,1,0));
  }

  void moveCameraRight() {
    cameraPos.x -= 0.05;
    cameraTarget.x -= 0.05;
    view = glm::lookAt(cameraPos, cameraTarget, glm::vec3(0,1,0));
  }

  void moveCameraUp() {
    cameraPos.y += 0.05;
    cameraTarget.y += 0.05;
    view = glm::lookAt(cameraPos, cameraTarget, glm::vec3(0,1,0));
  }

  void moveCameraDown() {
    cameraPos.y -= 0.05;
    cameraTarget.y -= 0.05;
    view = glm::lookAt(cameraPos, cameraTarget, glm::vec3(0,1,0));
  }
};

#endif
