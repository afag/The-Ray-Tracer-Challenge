#ifndef SPHEREH
#define SPHEREH
#include "tuple.h"
#include "ray.h"

struct record
{
  float t;
  tuple p;
  tuple normal;
  record(){}
};

class sphere
{
public:
  tuple center;
  double radius;
  sphere (tuple center, double radius): center(center), radius(radius){}
  bool hit(ray r, record& rec, double tmin, double tmax);
};

bool sphere::hit(ray r, record& rec, double tmin, double tmax)
{

  tuple oc = r.origin - center; // this is a vector
  float a = dot(r.direction, r.direction); // last ele must be zero;
  float b = 2.0 * dot(oc, r.direction);
  float c = dot(oc, oc) - radius * radius;
  float dis = b * b - 4 * a * c;

  if (dis > 0)
  { // double solutions, chose the smallest one
    float temp = (-b - sqrt(b * b - a * c)) / a;
    if (temp < tmax && temp > tmin)
    {
      rec.t = temp;
      rec.p = r.postion_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      return true;
    }

    temp = (-b + sqrt(b * b - a * c)) / a;
    if (temp < tmax && temp > tmin)
    {
      rec.t = temp;
      rec.p = r.postion_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      return true;
    }
  }
  return false;
}

#endif