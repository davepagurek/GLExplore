#ifndef GLSHADER_H
#define GLSHADER_H

#include <glad/glad.h>

class GLShader {
  public:
    GLShader(
      const char* vertexShaderFile,
      const char* fragmentShaderFile,
      const char* geometryShaderFile = nullptr);
    ~GLShader();

    void useProgram(); 
    GLuint getUniformLocation(const char* uniformName);

    // move shader uniform setting code here (may need to be templated with a bunch
    // of explicit specializations)

  private:
    GLuint shaderProgram = -1;
    GLuint vertexShader = -1, fragmentShader = -1, geometryShader = -1;
};

#endif
