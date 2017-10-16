#ifndef TRITABLE_H
#define TRITABLE_H

#include <glm/glm.hpp>
#include <utility>

extern const int triTable[256][13];

std::pair<glm::vec3, glm::vec3> getPositionAndNormal(
    int edgeVertexNum, float* densityCube, glm::vec3* gradientCube, float isoLevel = 0.0);

#endif
