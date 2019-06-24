#ifndef MATERIALH
#define MATERIALH
#include "color.h"
class material
{
public:
  double ambient;
  double diffuse;
  double specular;
  double shininess;
  color c;
  material()
  {
    ambient = 0.1;
    diffuse = 0.9;
    specular = 0.9;
    shininess = 200.0;
    c = color(1, 1, 1);
  }

  material &operator=(material rhs)
  {
    c = rhs.c;
    ambient = rhs.ambient;
    diffuse = rhs.diffuse;
    specular = rhs.specular;
    shininess = rhs.shininess;
    return *this;
  }
};

#endif