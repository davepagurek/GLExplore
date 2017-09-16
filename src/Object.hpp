#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object {
  public:
    virtual void draw(glm::mat4& projection, glm::mat4& view) = 0;
};

#endif
