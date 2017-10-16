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

uniform samplerCube depthMap;
uniform float farPlane;


float calculateShadow() {
  vec3 fragToLight =  FragPos - pointLightLocation[0];
  float currentDepth = length(fragToLight);
  float shadow = 0.0;
  float bias = max(0.05 * (1.0 - dot(Normal, fragToLight)), 0.005);
  float samples = 4.0;
  float offset = 0.1;

  // Blur shadow
  for(float x = -offset; x < offset; x += offset / (samples * 0.5)) {
    for(float y = -offset; y < offset; y += offset / (samples * 0.5)) {
      for(float z = -offset; z < offset; z += offset / (samples * 0.5)) {
        float closestDepth = texture(depthMap, fragToLight + vec3(x, y, z)).r;
        closestDepth *= farPlane;
        shadow += min(1.0, max(currentDepth - bias - closestDepth, 0));
      }
    }
  }
  shadow /= (samples * samples * samples);
  return 1.0-shadow;
}

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

    float shadow = i == 0 ? calculateShadow() : 1.0;

    color += diffuse * objectColor * shadow;

    reflectDir = reflect(-lightDir, norm);  
    spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    specular = specularStrength * spec * pointLightColor[i]; 

    color += specular * shadow;
  }
  FragColor = vec4(color, 1.0f);
}
