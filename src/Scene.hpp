#ifndef SCENE_H
#define SCENE_H

#include "Color.hpp"
#include "PointLight.hpp"

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Scene {

public:
  Scene(glm::mat4, glm::vec3, glm::vec3, Color, std::vector<PointLight>);

  // Accessors
  const Color&     getAmbientLight() const;
  const glm::vec3& getCameraPos()    const;
  const glm::vec3& getCameraTarget() const;
  const glm::mat4& getProjection()   const;
  const glm::mat4& getView()         const;
  const std::vector<PointLight>& getPointLights() const;

  // Camera movement
  void moveCameraLeft();
  void moveCameraRight();
  void moveCameraForward();
  void moveCameraBackward();
  void rotateCameraHorizontal(double);
  void rotateCameraVertical(double);

private:

  // Mutators
  void setView();

  static const glm::vec3 upVector;
  static const float stepSize;
  glm::vec3 cameraPos, cameraTarget;
  glm::mat4 projection, view;
  Color ambientLight;
  std::vector<PointLight> pointLights;

};

#endif
