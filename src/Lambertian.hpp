#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include <glad/glad.h> 
#include "Color.hpp"
#include "utils.hpp"
#include <string>
#include <vector>

class Lambertian {
  private:
    static bool shaderProgramCompiled;
    static unsigned int shaderProgram;
    static unsigned int vertexShader;
    static unsigned int fragmentShader;

    static const std::string vertexSource;
    static const std::string fragmentSource;

    Color diffuse;
    unsigned int VBO, VAO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    static void compileShaderProgramSource(const std::string& vertexSource, const std::string& fragmentSource) throw(ShaderProgramCompilationError);

  public:
    static void compileShaderProgram() throw(ShaderProgramCompilationError);

    Lambertian(Color diffuse, std::vector<float> vertices, std::vector<unsigned int> indices);
    void draw();
    static void cleanup();
};

#endif
