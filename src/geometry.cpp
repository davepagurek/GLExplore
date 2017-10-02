#include "geometry.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "utils.hpp"
#include "triTable.hpp"
#include "third_party/PerlinNoise/PerlinNoise.hpp"

std::vector<float> hills(int depth, int octaves) {
  siv::PerlinNoise noise(std::time(nullptr));
  std::vector<std::vector<float>> heights;
  std::vector<float> vertices;
  float maxHeightF = std::numeric_limits<float>::min();
  float minHeightF = std::numeric_limits<float>::max();

  // Create a grid of height values
  for (int i = 0; i < depth; i++) {
    heights.push_back({});
    for (int j = 0; j < depth; j++) {
      // Generate perlin noise for this x,z coordinate
      float height = noise.octaveNoise0_1(
          ((float)i)/((float)depth-1.0), ((float)j)/((float)depth-1.0), octaves) - 0.5;

      // Pull down the edges
      height -= std::pow(
        std::sqrt(
          std::pow(-0.5 + ((float)i)*(1.0/((float)depth-1.0)),2) +
          std::pow(-0.5 + ((float)j)*(1.0/((float)depth-1.0)),2)
        ) / 0.75,
        2
      );

      maxHeightF = std::max(height, maxHeightF);
      minHeightF = std::min(height, minHeightF);

      heights.back().push_back(height);
    }
  }

  int minHeight = minHeightF*100;
  int maxHeight = (int)maxHeightF*100 + 1;
  
  std::vector<std::vector<std::vector<float>>> density(
      depth, std::vector<std::vector<float>>(
          depth, std::vector<float>(maxHeight - minHeight, 0)));
  for (int x = 0; x < depth; x++) {
    for (int z = 0; z < depth; z++) {
      for (int y = 0; y < maxHeight - minHeight; y++) {
        density[x][z][y] = (y + minHeight)/100.0 - heights[x][z];
      }
    }
  }

  std::vector<std::vector<std::vector<glm::vec3>>> gradient(
      depth, std::vector<std::vector<glm::vec3>>(
          depth, std::vector<glm::vec3>(maxHeight - minHeight, glm::vec3(0, 0, 0))));
  for (int x = 0; x < depth; x++) {
    for (int z = 0; z < depth; z++) {
      for (int y = 0; y < maxHeight - minHeight; y++) {
        float dx1 = density[std::max(0, x - 1)][z][y];
        float dx2 = density[std::min(depth - 1, x + 1)][z][y];
        float dy1 = density[x][z][std::max(0, y - 1)];
        float dy2 = density[x][z][std::min(maxHeight - minHeight - 1, y + 1)];
        float dz1 = density[x][std::max(0, z - 1)][y];
        float dz2 = density[x][std::min(depth - 1, z + 1)][y];

        float gx = dx2 - dx1;
        float gy = dy2 - dy1;
        float gz = dz2 - dz1;

        gradient[x][z][y] = glm::normalize(glm::vec3(gx, gy, gz));
      }
    }
  }

  // The stuff below creates a disconnected mesh. I want to fix it later since it could
  // be useful for rendering stuff like spheres as isosurfaces, so the dead code is here
  // for now.
#if 0
  for (int x = 0; x < depth - 1; x++) {
    for (int z = 0; z < depth - 1; z++) {
      for (int y = 0; y < maxHeight - minHeight - 1; y++) {
        int triTableIdx = 0;
        for (int dx : {0, 1}) {
          for (int dz : {0, 1}) {
            for (int dy : {0, 1}) {
              if (density[x + dx][z + dz][y + dy] < 0) {
                triTableIdx |= 1 << (dy*4 + dz*2 + dx);
              }
            }
          }
        }

        int* triangleVertices = triTable[triTableIdx];
        float densityCube[8] = {
          density[x][z][y], density[x+1][z][y], density[x][z+1][y],
          density[x+1][z+1][y], density[x][z][y+1], density[x+1][z][y+1],
          density[x][z+1][y+1], density[x+1][z+1][y+1]
        };
        glm::vec3 gradientCube[8] = {
          gradient[x][z][y], gradient[x+1][z][y], gradient[x][z+1][y],
          gradient[x+1][z+1][y], gradient[x][z][y+1], gradient[x+1][z][y+1],
          gradient[x][z+1][y+1], gradient[x+1][z+1][y+1]
        };

        for (int* currentVertex = triangleVertices; *currentVertex != -1; currentVertex++) {
          glm::vec3 position, normal;
          std::tie(position, normal) = getPositionAndNormal(*currentVertex, densityCube, gradientCube);
          normal = glm::normalize(normal);
          
          float x1 = -0.5 + ((float)x + position.x)/(depth-1.0);
          float z1 = -0.5 + ((float)z + position.z)/(depth-1.0);
          float y1 = ((float)y + minHeight + position.y)/100.0;

          vertices.push_back(x1);
          vertices.push_back(y1);
          vertices.push_back(z1);
          vertices.push_back(normal.x);
          vertices.push_back(normal.y);
          vertices.push_back(normal.z);
        }
      }
    }
  }
#endif

  // Create triangle faces out of the height grid
  for (int i = 0; i < heights.size()-1; i++) {
    for (int j = 0; j < heights[i].size()-1; j++) {
      float x1 = -0.5 + ((float)i)*(1.0/((float)depth-1.0));
      float z1 = -0.5 + ((float)j)*(1.0/((float)depth-1.0));
      float y1 = heights[i][j];
      glm::vec3 n1 = gradient[i][j][y1*100 - minHeight];

      float x2 = -0.5 + ((float)(i+1))*(1.0/((float)depth-1.0));
      float z2 = -0.5 + ((float)j)*(1.0/((float)depth-1.0));
      float y2 = heights[i+1][j];
      glm::vec3 n2 = gradient[i+1][j][y2*100 - minHeight];

      float x3 = -0.5 + ((float)i)*(1.0/((float)depth-1.0));
      float z3 = -0.5 + ((float)(j+1))*(1.0/((float)depth-1.0));
      float y3 = heights[i][j+1];
      glm::vec3 n3 = gradient[i][j+1][y3*100 - minHeight];

      float x4 = -0.5 + ((float)(i+1))*(1.0/((float)depth-1.0));
      float z4 = -0.5 + ((float)(j+1))*(1.0/((float)depth-1.0));
      float y4 = heights[i+1][j+1];
      glm::vec3 n4 = gradient[i+1][j+1][y4*100 - minHeight];

      // Triangle 1
      vertices.push_back(x1);
      vertices.push_back(y1);
      vertices.push_back(z1);
      vertices.push_back(n1.x);
      vertices.push_back(n1.y);
      vertices.push_back(n1.z);

      vertices.push_back(x2);
      vertices.push_back(y2);
      vertices.push_back(z2);
      vertices.push_back(n2.x);
      vertices.push_back(n2.y);
      vertices.push_back(n2.z);

      vertices.push_back(x3);
      vertices.push_back(y3);
      vertices.push_back(z3);
      vertices.push_back(n3.x);
      vertices.push_back(n3.y);
      vertices.push_back(n3.z);

      // Triangle 2
      vertices.push_back(x4);
      vertices.push_back(y4);
      vertices.push_back(z4);
      vertices.push_back(n4.x);
      vertices.push_back(n4.y);
      vertices.push_back(n4.z);

      vertices.push_back(x3);
      vertices.push_back(y3);
      vertices.push_back(z3);
      vertices.push_back(n3.x);
      vertices.push_back(n3.y);
      vertices.push_back(n3.z);

      vertices.push_back(x2);
      vertices.push_back(y2);
      vertices.push_back(z2);
      vertices.push_back(n2.x);
      vertices.push_back(n2.y);
      vertices.push_back(n2.z);
    }
  }

  return vertices;
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

std::vector<float> sphere() {
  static constexpr float vertexLocations[] = {
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
  static constexpr int vertexIndices[] = {
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

    // Since this is a unit sphere, normals == positions
    vertices.push_back(vertexLocations[i*3]); // nx
    vertices.push_back(vertexLocations[i*3+1]); // ny
    vertices.push_back(vertexLocations[i*3+2]); // nz
  }

  // TODO: Accept a subdivision parameter and subdivide to make an icososphere

  return vertices;
}
