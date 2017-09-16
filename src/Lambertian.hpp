#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include <glad/glad.h> 
#include "Object.hpp"
#include "Color.hpp"
#include "utils.hpp"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Lambertian: public Object {
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
    glm::mat4 model;

    Lambertian(Color diffuse, std::vector<float> vertices, std::vector<unsigned int> indices);
    virtual void draw(glm::mat4& projection, glm::mat4& view);
    static void cleanup();
};

#endif
