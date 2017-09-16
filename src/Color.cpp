#include "Color.hpp"

Color::Color(long hex):
  red(((hex >> 32) & 0xFF) / 255.0),
  green(((hex >> 16) & 0xFF) / 255.0),
  blue(((hex >> 8) & 0xFF) / 255.0),
  alpha(((hex) & 0xFF) / 255.0)
{}

Color::Color(float red, float green, float blue, float alpha):
  red(red),
  green(green),
  blue(blue),
  alpha(alpha)
{}

float Color::r() const { return red; }
float Color::g() const { return green; }
float Color::b() const { return blue; }
float Color::a() const { return alpha; }
