#include "Lambertian.hpp"
#include <GLFW/glfw3.h>

bool Lambertian::shaderProgramCompiled = false;
unsigned int Lambertian::shaderProgram = 0;
unsigned int Lambertian::vertexShader = 0;
unsigned int Lambertian::fragmentShader = 0;
const std::string Lambertian::vertexSource =
#include "shaders/vertex.glsl"
;
const std::string Lambertian::fragmentSource =
#include "shaders/fragment.glsl"
;

Lambertian::Lambertian(Color diffuse, std::vector<float> vertices, std::vector<unsigned int> indices):
  diffuse(diffuse),
  vertices(vertices),
  indices(indices)
{
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glGenVertexArrays(1, &VAO);  
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices.front(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);
}

void Lambertian::compileShaderProgramSource(const std::string& vertexSource, const std::string& fragmentSource) throw(ShaderProgramCompilationError) {
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

void Lambertian::draw(glm::mat4& projection, glm::mat4& view) {
  model = glm::rotate(glm::mat4(), (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

  unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

  unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Lambertian::cleanup() {
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
