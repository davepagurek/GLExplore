#ifndef OBJECT_H
#define OBJECT_H

#include "Scene.hpp"

class Object {
  public:
    virtual void draw(Scene& scene) = 0;
};

#endif
