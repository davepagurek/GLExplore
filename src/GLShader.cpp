#include "GLShader.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "utils.hpp"

GLShader::GLShader(const char* vertexShaderFilename, const char* fragmentShaderFilename) {
  std::ifstream vertexShaderFile(vertexShaderFilename);
  std::string vertexSource = std::string(std::istream_iterator<char>(vertexShaderFile),
                           std::istream_iterator<char>());

  std::ifstream fragmentShaderFile(fragmentShaderFilename);
  std::string fragmentSource = std::string(std::istream_iterator<char>(fragmentShaderFile),
      std::istream_iterator<char>());

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
