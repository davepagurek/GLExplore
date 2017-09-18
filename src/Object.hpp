#ifndef OBJECT_H
#define OBJECT_H

#include "Scene.hpp"

class Object {
  public:
    virtual void draw(const Scene& scene) = 0;
};

#endif
