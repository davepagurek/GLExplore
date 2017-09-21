#ifndef GLSHADER_H
#define GLSHADER_H

#include <glad/glad.h>

class GLShader {
  public:
    GLShader(const char* vertexShaderFile, const char* fragmentShaderFile);
    ~GLShader();

    // should also declare
    // * which inputs the vertex shader takes (with dimensions - need to look into passing in arrays as shader inputs)
    // * uniform values to the pipeline (dimensions + array size)

  private:
    GLuint shaderProgram = -1;
    GLuint vertexShader = -1, fragmentShader = -1;
};

#endif
