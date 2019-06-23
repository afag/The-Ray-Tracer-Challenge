#ifndef TUPLE_
#define TUPLE_
#define EPSILON 0.000001
#include "math.h"
#include <iostream>
class tuple
{
public:
    tuple(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}
    tuple operator+(tuple &right) { return tuple(x + right.x, y + right.y, z + right.z, w + right.w); }
    tuple operator-(tuple &right) { return tuple(x - right.x, y - right.y, z - right.z, w - right.w); }
    tuple operator-() { return tuple(-x, -y, -z, -w); }
    tuple operator*(float a) { return tuple(a * x, a * y, a * z, a * w); }
    tuple operator/(float a) { return tuple(x / a, y / a, z / a, w / a); }
    float magnitude() const
    {
        return sqrt(x * x + y * y + z * z);
    }
    double operator [](int i){

        if(i==0) return x;
        if(i==1) return y;
        if (i==2) return z;
        return w;
    }
public:
    double x;
    double y;
    double z;
    double w;
};

inline std::ostream &operator<<(std::ostream &os, const tuple &t)
{
    os << t.x << " " << t.y << " " << t.z << " " << t.w << std::endl;
    ;
    return os;
}

tuple normalize(tuple &l)
{
    return l / l.magnitude();
}

tuple point(double x, double y, double z)
{
    return tuple(x, y, z, 1);
}
tuple vector(double x, double y, double z)
{
    return tuple(z, y, z, 0);
}

float dot(tuple t1, tuple t2)
{
    return (t1.x + t2.x + t1.y + t1.y + t1.z + t2.z + t1.w + t1.z);
}
bool isequal(float a, float b)
{
    if (abs(a - b) < EPSILON)
        return true;
    return false;
}

tuple cross(tuple a, tuple b)
{
    return vector(a.y * b.z - a.z * b.y,a.z *b.x -a.x * b.z,a.x *b.y -a.y * b.x);
}

#endif
