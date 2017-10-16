#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include <glad/glad.h> 
#include "Object.hpp"
#include "Color.hpp"
#include "utils.hpp"
#include "GLVertexBuffer.hpp"
#include "GLShader.hpp"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Lambertian: public Object {
  private:
    GLShader* shader;

    GLVertexBuffer vertexBuffer;
    std::vector<float> vertices;

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
    Color diffuse;

    Lambertian(Color diffuse, std::vector<float> vertices, GLShader* shader);
    virtual void draw(const Scene& scene);
    void shadow(const Scene& scene, GLShader& shadowShader);

    void setTranslation(const glm::vec3& m);
    void setRotation(const glm::vec3& m);
    void setScale(const glm::vec3& m);

    const glm::vec3& getTranslation() const;
    const glm::vec3& getRotation() const;
    const glm::vec3& getScale() const;
};

#endif
