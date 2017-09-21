#ifndef GLVERTEXBUFFER_H
#define GLVERTEXBUFFER_H

#include <vector>
#include <utility>

#include "utils.hpp"

class GLVertexBuffer {
  public:
    GLVertexBuffer(std::vector<std::pair<int, int>> dims)
      : attributeDimensions(std::move(dims))
    {
      for (const auto& dim : attributeDimensions) {
        strideLength += dim.first * dim.second;
      }
    }

    ~GLVertexBuffer() {}
    
    template <typename NumericType>
    void generateBuffersFromData(std::vector<NumericType>* data);

    void enableBuffer() { glBindVertexArray(VAO); }
    void disableBuffer() { glBindVertexArray(0); }

    int getNumVertices() { return numVertices; }

  private:
    std::vector<std::pair<int, int>> attributeDimensions;
    int numVertices = 0;
    int strideLength = 0;   // independent of numeric type size
    unsigned int VBO, VAO;
};

template <typename NumericType>
void GLVertexBuffer::generateBuffersFromData(std::vector<NumericType>* data) {
  numVertices = data->size() / strideLength;

  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, data->size()*sizeof(NumericType), &data->front(), GL_STATIC_DRAW);

  enableBuffer();

  int64_t offset = 0;
  for (int i = 0; i < attributeDimensions.size(); i++) {
    GLint dimSize = attributeDimensions[i].first * attributeDimensions[i].second;

    glVertexAttribPointer(i, dimSize, numericTypeToEnum<NumericType>(),
                          GL_FALSE, strideLength*sizeof(NumericType), (GLvoid*)offset);
    glEnableVertexAttribArray(i);

    offset += dimSize*sizeof(NumericType);
  }

  // Disable VAO for now; will enable before drawing.
  disableBuffer();
}

#endif
