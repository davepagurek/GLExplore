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
      vertexAttribFirstPtr = vertexAttribNextPtr;             
      vertexAttribNextPtr += attributeDimensions.size();

      for (const auto& dim : attributeDimensions) {
        strideLength += dim.first * dim.second;
      }
    }

    ~GLVertexBuffer() {}
    
    template <typename NumericType, size_t BufferSize>
    void generateBuffersFromData(NumericType data[BufferSize]);

    void enableBuffers() { glBindVertexArray(VAO); }

    int getNumVertices() { return numVertices; }

  private:
    std::vector<std::pair<int, int>> attributeDimensions;
    int vertexAttribFirstPtr;
    int numVertices = 0;
    int strideLength = 0;   // independent of numeric type size
    unsigned int VBO, VAO;

    static int vertexAttribNextPtr;
};

template <typename NumericType, size_t BufferSize>
void GLVertexBuffer::generateBuffersFromData(NumericType data[BufferSize]) {
  numVertices = BufferSize / strideLength;

  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, BufferSize*sizeof(float), data, GL_STATIC_DRAW);

  glBindVertexArray(VAO);

  int offset = 0;
  for (unsigned int i = 0; i < attributeDimensions.size(); i++) {
    GLuint currVertexAttrib = i + vertexAttribFirstPtr;
    GLint dimSize = attributeDimensions[i].first * attributeDimensions[i].second;

    glVertexAttribPointer(currVertexAttrib, dimSize, numericTypeToEnum<NumericType>(),
                          GL_FALSE, strideLength * sizeof(NumericType), (GLvoid*)offset);
    glEnableVertexAttribArray(currVertexAttrib);

    offset += dimSize;
  }

  // Unbind the VAO for now, and re-bind it when we want to draw
  glBindVertexArray(0);
}

#endif
