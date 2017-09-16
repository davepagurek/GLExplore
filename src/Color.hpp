#ifndef COLOR_H
#define COLOR_H

class Color {
  float red, green, blue, alpha;

  public:
    Color(long hex);
    Color(float red, float green, float blue, float alpha);
    float r() const;
    float g() const;
    float b() const;
    float a() const;
};

#endif
