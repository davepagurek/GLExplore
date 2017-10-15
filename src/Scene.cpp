#include "Scene.hpp"
#include <iostream>
#include "glm/ext.hpp"

Scene::Scene(glm::mat4 projection, glm::vec3 cameraPos, glm::vec3 cameraTarget, Color ambientLight,
      std::vector<PointLight> pointLights):
  cameraPos(cameraPos),
  cameraTarget(cameraTarget),
  projection(projection),
  view(glm::lookAt(cameraPos, cameraTarget, Scene::upVector)), ambientLight(ambientLight),
  pointLights(std::move(pointLights)) {}

// Accessors

const Color& Scene::getAmbientLight() const {
  return ambientLight;
}

const glm::vec3& Scene::getCameraPos() const {
  return cameraPos;
}

const glm::vec3& Scene::getCameraTarget() const {
  return cameraTarget;
}

const glm::mat4& Scene::getProjection() const {
  return projection;
}

const glm::mat4& Scene::getView() const {
  return view;
}

const std::vector<PointLight>& Scene::getPointLights() const {
  return pointLights;
}

// Camera movement

void Scene::moveCameraLeft() {
  float PI_BY_2 = glm::pi<float>() / 2.0;
  glm::vec3 dir = glm::normalize(cameraTarget - cameraPos);
  dir = glm::rotateY(dir, PI_BY_2) * stepSize;
  cameraTarget += dir;
  cameraPos += dir;
  setView();
}

void Scene::moveCameraRight() {
  float PI_BY_2 = glm::pi<float>() / 2.0;
  glm::vec3 dir = glm::normalize(cameraTarget - cameraPos);
  dir = glm::rotateY(dir, -1 * PI_BY_2) * stepSize;
  cameraTarget += dir;
  cameraPos += dir;
  setView();
}

void Scene::moveCameraForward() {
  glm::vec3 direction = glm::normalize(cameraTarget - cameraPos) * stepSize;
  cameraPos += direction;
  cameraTarget += direction;
  setView();
}

void Scene::moveCameraBackward() {
  glm::vec3 direction = glm::normalize(cameraTarget - cameraPos) * stepSize;
  cameraPos -= direction;
  cameraTarget -= direction;
  setView();
}

void Scene::rotateCameraHorizontal(double f) {
  float factor = glm::sqrt(2 - 2 * glm::cos(f)) / 80.0;
  if (f >= 0) {
      factor *= -1;
  }
  glm::vec3 forwardVec = (cameraTarget - cameraPos);
  cameraTarget = cameraPos + glm::rotateY(forwardVec, factor);
  setView();
}

void Scene::rotateCameraVertical(double f) {
  float factor = glm::sqrt(2 - 2 * glm::cos(f)) / 80.0;
  if (f < 0) {
      factor *= -1;
  }
  glm::vec3 forwardVec = (cameraTarget - cameraPos);
  cameraTarget = cameraPos + glm::rotateX(forwardVec, factor);
  setView();
}

// Mutators

void Scene::setView() {
  view = glm::lookAt(cameraPos, cameraTarget, Scene::upVector);
}

const glm::vec3 Scene::upVector(0, 1, 0);
const float Scene::stepSize = 0.05;
