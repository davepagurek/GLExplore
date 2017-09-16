#include "Lambertian.hpp"

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

void Lambertian::draw() {
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Lambertian::cleanup() {
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
