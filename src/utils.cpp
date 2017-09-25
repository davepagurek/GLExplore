#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ShaderProgramCompilationError::ShaderProgramCompilationError(std::string message):
  message(message) {}

std::string ShaderProgramCompilationError::getMessage() {
  return message;
}

unsigned int compileShader(const char source[], int type) throw(ShaderProgramCompilationError) {
  unsigned int shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    throw ShaderProgramCompilationError(std::string(infoLog));
  }

  return shader;
}

template<>
GLenum numericTypeToEnum<GLfloat>() { return GL_FLOAT; }

template<>
GLenum numericTypeToEnum<GLint>() { return GL_INT; }

// TODO: add more specializations

std::string slurp(const char* filename) {
  std::ifstream file(filename);
  std::stringstream fileContentStream;
  fileContentStream << file.rdbuf();

  // Copy the file contents before returning
  std::string fileContents = fileContentStream.str();
  return fileContents;
}

std::vector<float> addNormals(const std::vector<float>& vertices) {
  std::vector<float> withNormals;
  for (int i = 0; i < vertices.size(); i += 9) {
    float x1 = vertices[i];
    float y1 = vertices[i+1];
    float z1 = vertices[i+2];
    float x2 = vertices[i+3];
    float y2 = vertices[i+4];
    float z2 = vertices[i+5];
    float x3 = vertices[i+6];
    float y3 = vertices[i+7];
    float z3 = vertices[i+8];

    glm::vec3 v1(x3-x2, y3-y2, z3-z2);
    glm::vec3 v2(x1-x2, y1-y2, z1-z2);
    glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

    // Make both front and back faces
    for (float multiplier : { -1, 1 }) {
      withNormals.push_back(x1);
      withNormals.push_back(y1);
      withNormals.push_back(z1);
      withNormals.push_back(normal.x * multiplier);
      withNormals.push_back(normal.y * multiplier);
      withNormals.push_back(normal.z * multiplier);

      withNormals.push_back(x2);
      withNormals.push_back(y2);
      withNormals.push_back(z2);
      withNormals.push_back(normal.x * multiplier);
      withNormals.push_back(normal.y * multiplier);
      withNormals.push_back(normal.z * multiplier);

      withNormals.push_back(x3);
      withNormals.push_back(y3);
      withNormals.push_back(z3);
      withNormals.push_back(normal.x * multiplier);
      withNormals.push_back(normal.y * multiplier);
      withNormals.push_back(normal.z * multiplier);
    }
  }

  return withNormals;
}
