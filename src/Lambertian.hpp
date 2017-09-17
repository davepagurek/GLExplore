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

    unsigned int VBO, VAO;
    std::vector<float> vertices;

    static void compileShaderProgramSource(const std::string& vertexSource, const std::string& fragmentSource) throw(ShaderProgramCompilationError);

  public:
    static void compileShaderProgram() throw(ShaderProgramCompilationError);
    glm::mat4 model;
    Color diffuse;

    Lambertian(Color diffuse, std::vector<float> vertices);
    virtual void draw(Scene& scene);
    static void cleanup();
};

#endif
