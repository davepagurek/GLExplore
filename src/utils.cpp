#include "utils.hpp"

ShaderProgramCompilationError::ShaderProgramCompilationError(std::string message):
  message(message) {}

std::string ShaderProgramCompilationError::getMessage() {
  return message;
}

unsigned int compileShader(const std::string& source, int type) throw(ShaderProgramCompilationError) {
  unsigned int shader = glCreateShader(type);
  const char* cShaderSource = source.c_str();
  glShaderSource(shader, 1, &cShaderSource, NULL);
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
