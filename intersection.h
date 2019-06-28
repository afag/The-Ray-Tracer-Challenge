#ifndef INTERSECTION
#define INTERSECTION
#include "shape.h"
#include"world.h"
class comp // delete this class;
{
public:
 comp(){}

 
  double t;
  tuple point;
  tuple eyev;
  tuple normalv;
  bool inside; // used to have a correct normal direction;
  //sphere s;
 void prepare_computaion(world w,  ray r, int which_t, std::vector<std::pair<double, int>> intersect);
};
void  comp::prepare_computaion(world w,  ray r, int which_t, std::vector<std::pair<double, int>> intersect){

      double t=intersect[which_t].first;
      shape* s=w.groups[intersect[which_t].second];
      point=r.postion_at_parameter(t); // hittting point
      normalv =s->normal_at(point);
      normalv=normalize(normalv);
      eyev=-r.direction/r.direction.magnitude();
     if(dot(normalv,eyev)<0){
       inside=true;
       normalv=-normalv;
       std::cout<<"inside"<<std::endl;
     }
     else {
       inside=false;
       std::cout<<"outside"<<std::endl;
     }

}


#endif