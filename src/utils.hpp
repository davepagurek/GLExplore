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

struct GLNumericTypeError {};

unsigned int compileShader(const char source[], int type) throw(ShaderProgramCompilationError);

// Explicit specializations provided in .cpp file
template<typename NumericType>
GLenum numericTypeToEnum() { throw GLNumericTypeError(); }

// Read the entire contents of a file.
std::string slurp(const char* filename);

#endif
