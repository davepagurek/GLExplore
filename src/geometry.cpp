#include "geometry.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils.hpp"
#include "third_party/PerlinNoise/PerlinNoise.hpp"

std::vector<float> hills(int depth, int octaves) {
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

std::vector<float> cube() {
  return addNormals({
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
  });
}

namespace {
  glm::vec3 normalize(const glm::vec3 a, const glm::vec3 b) {
    float length = 1.0;
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float dz = b.z - a.z;
    float distance = glm::distance(a,b);
    dx *= length / distance;
    dy *= length / distance;
    dz *= length / distance;

    return glm::vec3(a.x+dx, a.y+dy, a.z+dz);
  }
}

std::vector<float> sphere() {
  float vertexLocations[] = {
    0, -0.525731, 0.850651,             // vertices[0]
    0.850651, 0, 0.525731,              // vertices[1]
    0.850651, 0, -0.525731,             // vertices[2]
    -0.850651, 0, -0.525731,            // vertices[3]
    -0.850651, 0, 0.525731,             // vertices[4]
    -0.525731, 0.850651, 0,             // vertices[5]
    0.525731, 0.850651, 0,              // vertices[6]
    0.525731, -0.850651, 0,             // vertices[7]
    -0.525731, -0.850651, 0,            // vertices[8]
    0, -0.525731, -0.850651,            // vertices[9]
    0, 0.525731, -0.850651,             // vertices[10]
    0, 0.525731, 0.850651              // vertices[11]
  };
  int vertexIndices[] = {
    6, 2, 1,
    2, 7, 1,
    5, 4, 3,
    8, 3, 4,
    11, 5, 6,
    10, 6, 5,
    2, 10, 9,
    3, 9, 10,
    9, 8, 7,
    0, 7, 8,
    1, 0, 11,
    4, 11, 0,
    10, 2, 6,
    11, 6, 1,
    10, 5, 3,
    11, 4, 5,
    9, 7, 2,
    0, 1, 7,
    8, 9, 3,
    0, 8, 4,
  };
  std::vector<float> vertices;
  for (int i : vertexIndices) {
    vertices.push_back(vertexLocations[i*3]); // x
    vertices.push_back(vertexLocations[i*3+1]); // y
    vertices.push_back(vertexLocations[i*3+2]); // z
  }

  return addNormals(vertices);
}
