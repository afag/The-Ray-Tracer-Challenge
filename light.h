#ifndef LIGHTH
#define LIGHTH
#include "tuple.h"
#include "color.h"
class light
{
public:
  tuple position;
  color intensity;

  light(tuple position, color intensity) : position(position), intensity(intensity) {}
};

#endif