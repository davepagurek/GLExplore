#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include <glad/glad.h> 
#include "Object.hpp"
#include "Color.hpp"
#include "utils.hpp"
#include "GLVertexBuffer.hpp"
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

    static const char vertexSource[];
    static const char fragmentSource[];

    GLVertexBuffer vertexBuffer;
    std::vector<float> vertices;

    static void compileShaderProgramSource(const char vertexSource[], const char fragmentSource[]) throw(ShaderProgramCompilationError);

    void generateBuffers();
    void updateModel();

    glm::mat4 model;
    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;

    static const glm::vec3 xAxis;
    static const glm::vec3 yAxis;
    static const glm::vec3 zAxis;

  public:
    static void compileShaderProgram() throw(ShaderProgramCompilationError);
    Color diffuse;

    Lambertian(Color diffuse, std::vector<float> vertices);
    virtual void draw(const Scene& scene);
    static void cleanup();

    void setTranslation(const glm::vec3& m);
    void setRotation(const glm::vec3& m);
    void setScale(const glm::vec3& m);

    const glm::vec3& getTranslation() const;
    const glm::vec3& getRotation() const;
    const glm::vec3& getScale() const;
};

#endif
