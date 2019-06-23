#ifndef CANVASH
#define CANVASH
#include "color.h"
#include <fstream>
#include<string>
class canvas
{

public:
    int width;
    int height;

    color *c;
    canvas(int width, int height) : width(width), height(height)
    {
        c = new color[width * height];
    }

};

inline void write_pixel(canvas can, int x, int y, color c)
{
    can.c[y * can.width + x].r = c.r;
    can.c[y * can.width + x].g = c.g;
    can.c[y * can.width + x].b = c.b;
}

inline void canvas2ppm(canvas can, std::string filename)
{

    std::ofstream out(filename);
    out << "P3" << std::endl;
    out << can.width << " " << can.height << std::endl;
    out << 255 << std::endl;

    for (int i = 0; i < can.height; i++)
    {
        for (int j = 0;j < can.width; j++)
        {
            out << can.c[i * can.width + j];
        }
    }
}

#endif