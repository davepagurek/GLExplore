#include "Scene.hpp"

Scene::Scene(glm::mat4 projection, glm::vec3 cameraPos, glm::vec3 cameraTarget, Color ambientLight,
      std::vector<PointLight> pointLights, float farPlane):
  cameraPos(cameraPos),
  cameraTarget(cameraTarget),
  projection(projection),
  view(glm::lookAt(cameraPos, cameraTarget, Scene::upVector)),
  ambientLight(ambientLight),
  pointLights(std::move(pointLights)),
  farPlane(farPlane)
{}

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

const float Scene::getFarPlane() const {
  return farPlane;
}

// Camera movement

void Scene::moveCameraLeft() {
  cameraPos.x += 0.05;
  cameraTarget.x += 0.05;
  setView();
}

void Scene::moveCameraRight() {
  cameraPos.x -= 0.05;
  cameraTarget.x -= 0.05;
  setView();
}

void Scene::moveCameraForward() {
  cameraPos.z += 0.05;
  cameraTarget.z += 0.05;
  setView();
}

void Scene::moveCameraBackward() {
  cameraPos.z -= 0.05;
  cameraTarget.z -= 0.05;
  setView();
}

// Mutators

void Scene::setView() {
  view = glm::lookAt(cameraPos, cameraTarget, Scene::upVector);
}

const glm::vec3 Scene::upVector(0, 1, 0);
