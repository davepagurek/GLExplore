#version 330 core
uniform vec3 objectColor;
uniform vec3 ambientColor;
uniform vec3 cameraPos;
uniform vec3 pointLightLocation[8];
uniform vec3 pointLightColor[8];
uniform int numPointLights;
in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

void main() {
  vec3 color = objectColor * ambientColor;
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(cameraPos - FragPos);
  float specularStrength = 0.3;
  float diff, spec;
  vec3 diffuse, specular;
  vec3 lightDir;
  vec3 reflectDir;
  int i;

  for (i = 0; i < numPointLights; i++) {
    lightDir = normalize(pointLightLocation[i] - FragPos);

    diff = max(dot(norm, lightDir), 0.0);
    diffuse = diff * pointLightColor[i];

    color += diffuse * objectColor;

    reflectDir = reflect(-lightDir, norm);  
    spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    specular = specularStrength * spec * pointLightColor[i]; 

    color += specular;
  }
  FragColor = vec4(color, 1.0f);
}
