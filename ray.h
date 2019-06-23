#ifndef RAYH
#define RAYH
#include "tuple.h"

class ray
{

public:
    ray(tuple origin, tuple direction) : origin(origin), direction(direction){};

public:
    tuple origin;
    tuple direction;
    double t;

    tuple postion_at_parameter(float t)
    {
        tuple temp = direction * t;

        //std::cout<<direction<<"...............";
        return origin + temp;
    }
    tuple getorigin()
    {

        return origin;
    }
};

#endif