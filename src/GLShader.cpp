#include "GLShader.hpp"

#include "utils.hpp"

GLShader::GLShader(const char* vertexShaderFilename, const char* fragmentShaderFilename) {
  std::string vertexSource = slurp(vertexShaderFilename);

  std::string fragmentSource = slurp(fragmentShaderFilename);

  vertexShader = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
  fragmentShader = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
}

GLShader::~GLShader() {
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void GLShader::useProgram() {
  glUseProgram(shaderProgram);
}

GLuint GLShader::getUniformLocation(const char* uniformName) {
  return glGetUniformLocation(shaderProgram, uniformName);
}
