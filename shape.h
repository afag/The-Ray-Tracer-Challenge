#ifndef SHAPEH
#define SHAPEH
#include "matrix.h"
#include "material.h"
#include "ray.h"

struct record
{
  float t1;
  float t2;
  tuple p1;
  tuple p2;
  tuple normal1;
  tuple normal2;
  record(){};
};

class shape
{
public:
  shape()
  {
    transform = Identity();
  }
  void set_transform(Matrix4d rhs)
  {
    transform = transform * rhs;
  }

  bool intersect(ray r, record &rec, double tmin, double tmax)
  {
    tuple origin = transform.inverse() * r.origin;
    tuple dir = transform.inverse() * r.direction;
    ray local_ray(origin, dir);

    bool res = local_intersect(local_ray, rec, tmin, tmax);
    return res;
  }

  tuple normal_at(tuple p)
  {
    tuple local_point = transform.inverse() * p;
    tuple local_normal = local_normal_at(local_point);
    tuple world_normal = transform.inverse().transpose() * local_normal;
    world_normal.w = 0;
    return normalize(world_normal);
  }
  virtual bool local_intersect(ray r, record &rec, double tmin, double tmax) = 0;
  virtual tuple local_normal_at(tuple local_point) = 0;
  material m;
  Matrix4d transform;
};

// sphere;
class sphere : public shape
{
public:
  tuple center;
  double radius;
  sphere(tuple center, double radius) : center(center), radius(radius) {}
  void assignmaterial(material m)
  {
    this->m = m;
  }
  virtual bool local_intersect(ray r, record &rec, double tmin, double tmax);
  virtual tuple local_normal_at(tuple local_point);
};

tuple sphere::local_normal_at(tuple local_point)
{

  tuple result = local_point - center;
  result.w = 0;
  return normalize(result);
}
bool sphere::local_intersect(ray r, record &rec, double tmin, double tmax)
{

  tuple oc = r.origin - center;            // this is a vector
  float a = dot(r.direction, r.direction); // last ele must be zero;
  float b = 2.0 * dot(oc, r.direction);
  float c = dot(oc, oc) - radius * radius;
  float dis = b * b - 4 * a * c;

  if (dis > 0)
  { // double solutions, chose the smallest one
    float temp = (-b - sqrt(b * b - 4 * a * c)) / (2.0 * a);
    if (temp < tmax && temp > tmin)
    {
      rec.t1 = temp;
      rec.p1 = r.postion_at_parameter(rec.t1);
      rec.normal1 = (rec.p1 - center) / radius;
      //return true;
    }

    temp = (-b + sqrt(b * b - 4 * a * c)) / (2.0 * a);
    if (temp < tmax && temp > tmin)
    {
      rec.t2 = temp;
      rec.p2 = r.postion_at_parameter(rec.t2);
      rec.normal2 = (rec.p2 - center) / radius;
      return true;
    }
  }
  return false;
};

class plane : public shape  // default plane is xz plane;
{

public:
  virtual bool local_intersect(ray r, record &rec, double tmin, double tmax);
  virtual tuple local_normal_at(tuple local_point);
};

tuple plane:: local_normal_at(tuple local_point)
  {

    return vector(0,1,0);
  }

bool plane::local_intersect(ray r, record &rec, double tmin, double tmax)
{
    if(abs(r.direction.y)<0.000000001)
    return false;

   double  t=-r.origin.y/r.direction.y;
   rec.t1=t;
   rec.t2=t;
   return true;
}
#endif