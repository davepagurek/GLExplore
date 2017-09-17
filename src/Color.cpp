#include "Color.hpp"

Color::Color(int hex):
  red(((hex >> 16) & 0xFF) / 255.0),
  green(((hex >> 8) & 0xFF) / 255.0),
  blue(((hex) & 0xFF) / 255.0)
{}

Color::Color(float red, float green, float blue):
  red(red),
  green(green),
  blue(blue)
{}

float Color::r() const { return red; }
float Color::g() const { return green; }
float Color::b() const { return blue; }
