#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include <string>

class ShaderProgramCompilationError {
  private:
    std::string message;
  public:
    ShaderProgramCompilationError(std::string message);
    std::string getMessage();
};

unsigned int compileShader(const char source[], int type) throw(ShaderProgramCompilationError);

#endif
