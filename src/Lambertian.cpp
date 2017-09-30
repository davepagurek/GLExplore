#include "Lambertian.hpp"
#include <GLFW/glfw3.h>
#include <utility>
#include <iostream>

const glm::vec3 Lambertian::xAxis(1, 0, 0);
const glm::vec3 Lambertian::yAxis(0, 1, 0);
const glm::vec3 Lambertian::zAxis(0, 0, 1);

Lambertian::Lambertian(Color diffuse, std::vector<float> vertices, GLShader* shader):
  shader(shader),
  vertexBuffer({{3, 1}, {3, 1}}),
  vertices(std::move(vertices)),
  model(glm::mat4()),
  translation(glm::vec3(0, 0, 0)),
  rotation(glm::vec3(0, 0, 0)),
  scale(glm::vec3(1, 1, 1)),
  diffuse(diffuse)
{
  vertexBuffer.generateBuffersFromData(&this->vertices);  
}

void Lambertian::draw(const Scene& scene) {
  unsigned int modelLoc = shader->getUniformLocation("model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

  unsigned int viewLoc = shader->getUniformLocation("view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(scene.getView()));

  unsigned int projectionLoc = shader->getUniformLocation("projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(scene.getProjection()));

  unsigned int cameraPosLoc = shader->getUniformLocation("cameraPos");
  glUniform3f(cameraPosLoc, scene.getCameraPos().x, scene.getCameraPos().y, scene.getCameraPos().z);

  unsigned int objectColorLoc = shader->getUniformLocation("objectColor");
  glUniform3f(objectColorLoc, diffuse.r(), diffuse.g(), diffuse.b());

  unsigned int ambientColorLoc = shader->getUniformLocation("ambientColor");
  glUniform3f(ambientColorLoc, scene.getAmbientLight().r(), scene.getAmbientLight().g(), scene.getAmbientLight().b());

  unsigned int numPointLightsLoc = shader->getUniformLocation("numPointLights");
  glUniform1i(numPointLightsLoc, scene.getPointLights().size());

  glm::vec3 pointLightLocation[8];
  glm::vec3 pointLightColor[8];
  for (int i = 0; i < 8 && i < scene.getPointLights().size(); i++) {
    const PointLight& p = scene.getPointLights()[i];
    pointLightLocation[i] = p.location;
    pointLightColor[i] = glm::vec3(p.color.r(), p.color.g(), p.color.b());
  }

  unsigned int pointLightLocationLoc = shader->getUniformLocation("pointLightLocation");
  glUniform3fv(pointLightLocationLoc, 8, glm::value_ptr(pointLightLocation[0]));

  unsigned int pointLightColorLoc = shader->getUniformLocation("pointLightColor");
  glUniform3fv(pointLightColorLoc, 8, glm::value_ptr(pointLightColor[0]));

  vertexBuffer.enableBuffer();
  glDrawArrays(GL_TRIANGLES, 0, vertexBuffer.getNumVertices());
  vertexBuffer.disableBuffer();
}

void Lambertian::shadow(const Scene& scene, GLShader& shadowShader) {
  unsigned int modelLoc = shadowShader.getUniformLocation("model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

  vertexBuffer.enableBuffer();
  glDrawArrays(GL_TRIANGLES, 0, vertexBuffer.getNumVertices());
  vertexBuffer.disableBuffer();
}

void Lambertian::setTranslation(const glm::vec3& v) {
  translation = v;
  updateModel();
}

void Lambertian::setRotation(const glm::vec3& v) {
  rotation = v;
  updateModel();
}

void Lambertian::setScale(const glm::vec3& v) {
  scale = v;
  updateModel();
}

const glm::vec3& Lambertian::getTranslation() const {
  return translation;
}

const glm::vec3& Lambertian::getRotation() const {
  return rotation;
}

const glm::vec3& Lambertian::getScale() const {
  return scale;
}

void Lambertian::updateModel() {
  model = glm::translate(glm::mat4(), translation);
  model = glm::rotate(model, rotation.x, xAxis);
  model = glm::rotate(model, rotation.y, yAxis);
  model = glm::rotate(model, rotation.z, zAxis);
  model = glm::scale(model, scale);
}
