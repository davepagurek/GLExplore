#include "GLShader.hpp"

#include "utils.hpp"

GLShader::GLShader(
    const char* vertexShaderFilename,
    const char* fragmentShaderFilename,
    const char* geometryShaderFilename) {
  std::string vertexSource = slurp(vertexShaderFilename);
  std::string fragmentSource = slurp(fragmentShaderFilename);

  vertexShader = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
  fragmentShader = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  if (geometryShaderFilename) {
    std::string geometryShaderSource = slurp(geometryShaderFilename);
    geometryShader = compileShader(geometryShaderSource.c_str(), GL_GEOMETRY_SHADER);
    glAttachShader(shaderProgram, geometryShader);
  }
  glLinkProgram(shaderProgram);
}

GLShader::~GLShader() {
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  if (geometryShader != -1) {
    glDeleteShader(geometryShader);
  }
}

void GLShader::useProgram() {
  glUseProgram(shaderProgram);
}

GLuint GLShader::getUniformLocation(const char* uniformName) {
  return glGetUniformLocation(shaderProgram, uniformName);
}
