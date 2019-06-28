#ifndef WORLDH
#define WORLDH
#include "light.h"
#include "shape.h"
#include <vector>
#include <utility>
#include <algorithm>
class world
{

public:
  world() : l(light(point(-10, 10, -10), color(1, 1, 1))), s1(sphere(point(0, 0, 0), 1)), s2(sphere(point(0, 0, 0), 0.5))
  {
    s1.m.c = color(0.8, 1.0, 0.6);
    s1.m.diffuse = 0.7;
    s1.m.specular = 0.2;
    s2.m.c = color(0.8, 1.0, 0.6);
    s2.m.diffuse = 0.7;
    s2.m.specular = 0.2;

    // groups.push_back(&s1);
    // groups.push_back(&s2);
  }
  light l;
  sphere s1;
  sphere s2;

  std::vector<shape *> groups;
};

bool compare(const std::pair<double, int> &i, const std::pair<double, int> &j)
{
  return i.first < j.first;
}
bool intersect_world(world &d, record &rec, ray r, std::vector<std::pair<double, int>> &intersect)
{

  bool found = false;
  std::cout << "Before sorting " << std::endl;
  for (int i = 0; i < d.groups.size(); i++)
  {

    shape *s = d.groups[i];
    if (s->intersect(r, rec, -100000, 1000000))
    {
      found = true;
      std::pair<double, int> p1 = std::make_pair(rec.t1, i);
      std::pair<double, int> p2 = std::make_pair(rec.t2, i);

      intersect.push_back(p1);
      intersect.push_back(p2);

      std::cout << p1.first << "\t" << i << std::endl;
      std::cout << p2.first << "\t" << i << std::endl;
    }
  }

  if (found)
  {
    std::sort(intersect.begin(), intersect.end());

    std::cout << "After sorting" << std::endl;

    for (int i = 0; i < intersect.size(); i++)
    {
      std::cout << intersect[i].first << "\t" << intersect[i].second << std::endl;
    }
  }

  return found;
}

bool is_shadowed(world w, tuple point)
{

  tuple v = w.l.position - point;
  double distance = v.magnitude();
  tuple direction = normalize(v);

  ray r = ray(point, direction);

  record rec;
  std::vector<std::pair<double, int>> intersect;

  std::cout<<"..................++++++++++++++++.............................................."<<std::endl;
  if (!intersect_world(w, rec, r, intersect))
  { //std::cout<<" ...................................................I must not be a shadow"<<std::endl;
    return false;
  }
  std::cout<<"....................+++++++++++++++++++.............................................."<<std::endl;
  double index = -1;
  for (int i = 0; i < intersect.size(); i++)
  {
    if (intersect[i].first >= 0)
    {
      index = i;
      break;
    }
  }
  if(index==-1) return false;
  std::cout << "shadowed  " << intersect[index].second << std::endl;
  //getchar();
  if (intersect[index].first < distance)
    return true;

  return false;
}
#endif