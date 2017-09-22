#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

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
