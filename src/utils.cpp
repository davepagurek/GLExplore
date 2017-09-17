#include "utils.hpp"

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
