#ifndef TRANSFORMATIONH
#define TRANSFORMATIONH
#include "matrix.h"

Matrix4d translation(double x, double y, double z)
{

    double res[16] = {0};
    // memset(res, 0, sizeof(double)*16);
    res[0] = 1;
    res[3] = x;
    res[1 + 4] = 1;
    res[7] = y;
    res[2 + 8] = 1;
    res[11] = z;
    res[15] = 1;
    return Matrix4d(res);
}

Matrix4d scale(double x, double y, double z)
{

    double res[16] = {0};
    res[0] = x;
    res[5] = y;
    res[10] = z;
    res[15] = 1;

    return Matrix4d(res);
}

Matrix4d rotation_x(double radian)
{
    double res[16] = {0};
    res[0] = 1;
    res[5] = cos(radian);
    res[6] = -sin(radian);
    res[9] = sin(radian);
    res[10] = cos(radian);
    res[15] = 1;
    return Matrix4d(res);
}

Matrix4d rotation_y(double radian)
{
    double res[16] = {0};
    res[0] = cos(radian);
    res[2] = sin(radian);
    res[5] = 1;
    res[8] = -sin(radian);
    res[10] = cos(radian);
    res[15] = 1;
    return Matrix4d(res);
}

Matrix4d rotation_z(double radian)
{
    double res[16] = {0};
    res[0] = cos(radian);
    res[1] = -sin(radian);
    res[4] = sin(radian);
    res[5] = cos(radian);
    res[10] = 1;
    res[15] = 1;
    return Matrix4d(res);
}

#endif