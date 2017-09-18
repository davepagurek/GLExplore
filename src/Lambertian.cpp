#include "Lambertian.hpp"
#include <GLFW/glfw3.h>
#include <utility>

bool Lambertian::shaderProgramCompiled = false;
unsigned int Lambertian::shaderProgram = 0;
unsigned int Lambertian::vertexShader = 0;
unsigned int Lambertian::fragmentShader = 0;
const char Lambertian::vertexSource[] =
#include "shaders/vertex.glsl"
;
const char Lambertian::fragmentSource[] =
#include "shaders/fragment.glsl"
;
#include <iostream>

Lambertian::Lambertian(Color diffuse, std::vector<float> vertices):
  vertices(std::move(vertices)),
  diffuse(diffuse)
{
  generateBuffers();
}

void Lambertian::generateBuffers() {
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices.front(), GL_STATIC_DRAW);

  glBindVertexArray(VAO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void Lambertian::compileShaderProgramSource(const char vertexSource[], const char fragmentSource[]) throw(ShaderProgramCompilationError) {
  vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
  fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
}

void Lambertian::compileShaderProgram() throw(ShaderProgramCompilationError) {
  compileShaderProgramSource(vertexSource, fragmentSource);
}

void Lambertian::draw(const Scene& scene) {
  // todo move this rotation out of here so it's more generic
  glm::mat4 transformed = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
  transformed = glm::rotate(transformed, (float)glfwGetTime(), glm::vec3(0.0f, 0.2f, 0.0f));
  glUseProgram(shaderProgram);

  unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transformed));

  unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(scene.getView()));

  unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(scene.getProjection()));

  unsigned int cameraPosLoc = glGetUniformLocation(shaderProgram, "cameraPos");
  glUniform3f(cameraPosLoc, scene.getCameraPos().x, scene.getCameraPos().y, scene.getCameraPos().z);

  unsigned int objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");
  glUniform3f(objectColorLoc, diffuse.r(), diffuse.g(), diffuse.b());

  unsigned int ambientColorLoc = glGetUniformLocation(shaderProgram, "ambientColor");
  glUniform3f(ambientColorLoc, scene.getAmbientLight().r(), scene.getAmbientLight().g(), scene.getAmbientLight().b());

  unsigned int numPointLightsLoc = glGetUniformLocation(shaderProgram, "numPointLights");
  glUniform1i(numPointLightsLoc, scene.getPointLights().size());

  glm::vec3 pointLightLocation[8];
  glm::vec3 pointLightColor[8];
  for (int i = 0; i < 8 && i < scene.getPointLights().size(); i++) {
    const PointLight& p = scene.getPointLights()[i];
    pointLightLocation[i] = p.location;
    pointLightColor[i] = glm::vec3(p.color.r(), p.color.g(), p.color.b());
  }

  unsigned int pointLightLocationLoc = glGetUniformLocation(shaderProgram, "pointLightLocation");
  glUniform3fv(pointLightLocationLoc, 8, glm::value_ptr(pointLightLocation[0]));

  unsigned int pointLightColorLoc = glGetUniformLocation(shaderProgram, "pointLightColor");
  glUniform3fv(pointLightColorLoc, 8, glm::value_ptr(pointLightColor[0]));

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);//vertices.size()/6);
}

void Lambertian::cleanup() {
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
