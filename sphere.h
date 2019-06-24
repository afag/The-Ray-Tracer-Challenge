#ifndef SPHEREH
#define SPHEREH
#include "tuple.h"
#include "ray.h"
#include "material.h"
struct record
{
  float t;
  tuple p;
  tuple normal;
  record() {}
};

class sphere
{
public:
  material m;
  tuple center;
  double radius;
  sphere(tuple center, double radius) : center(center), radius(radius) {}
  void assignmaterial(material m){
    this->m=m;
  }
  bool hit(ray r, record &rec, double tmin, double tmax);
};

bool sphere::hit(ray r, record &rec, double tmin, double tmax)
{

  tuple oc = r.origin - center;            // this is a vector
  float a = dot(r.direction, r.direction); // last ele must be zero;
  float b = 2.0 * dot(oc, r.direction);
  float c = dot(oc, oc) - radius * radius;
  float dis = b * b - 4 * a * c;

  if (dis > 0)
  { // double solutions, chose the smallest one
    float temp = (-b - sqrt(b * b - 4*a * c)) / (2.0*a);
    if (temp < tmax && temp > tmin)
    {
      rec.t = temp;
      rec.p = r.postion_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      return true;
    }

    temp = (-b + sqrt(b * b - 4*a * c)) / (2.0*a);
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

tuple normalat(sphere s, tuple p)
{
  tuple result = p - s.center;
  result.w = 0;
  return normalize(result);
}

#endif