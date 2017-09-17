#ifndef COLOR_H
#define COLOR_H

class Color {
  float red, green, blue;

  public:
    Color(int hex);
    Color(float red, float green, float blue);
    float r() const;
    float g() const;
    float b() const;
};

#endif
