#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include <string>
#include <vector>

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


// Take a float array of face vertex coordinates and insert normals after each vertex
std::vector<float> addNormals(const std::vector<float>& vertices);

template<typename T>
T lerp(T v1, T v2, float weight) {
  return weight*v1 + (1-weight)*v2;
}

#endif
