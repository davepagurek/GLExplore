#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Color.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct PointLight {
  Color color;
  glm::vec3 location;
};

#endif
