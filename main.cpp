#include "tuple.h"
#include "color.h"
#include "canvas.h"
#include "matrix.h"
#include "transformation.h"
#include "ray.h"
#include "light.h"
#include "world.h"
#include "intersection.h"
#include "camera.h"
#include"shape.h"
color lightning(material m, light l, tuple pos, tuple eye, tuple normal, bool is_shadowed)
{

    color res;
    // combine surface color with light's color;
    color effective_color = m.c * l.intensity;
    tuple tmp1 = l.position - pos;
    // find the direction to the light source;
    tuple lightv = normalize(tmp1);
    // compute the ambient contribution;
    color ambient = effective_color * m.ambient;
    res = res + ambient;
    if (is_shadowed) return res;
    // check whether light normal is on the other side of the surface;
    double light_dot_normal = dot(lightv, normal);
    if (light_dot_normal < 0)
    {
        return res;
    }

    else
    {
        color diffuse = effective_color * m.diffuse * light_dot_normal;
        res = res + diffuse;
    }

    tuple reflectv = reflect(-lightv, normal);
    double reflect_dot_eye = dot(reflectv, eye);

    if (reflect_dot_eye <= 0)
    {
        return res;
    }

    else
    {
        double factor = pow(reflect_dot_eye, m.shininess);
        color specular = l.intensity * m.specular * factor;

        return res + specular;
    }
}

color shade_hit(world w, comp com, material m)
{   tuple temp=com.normalv*0.001;
    com.point=com.point+temp;
    bool isshadowed=is_shadowed(w, com.point);   
   // if(shadowed) return color (0.1,0.1,0.1);
    color c = lightning(m, w.l, com.point, com.eyev, com.normalv, isshadowed);
    return c;
}


color colorat(world w, ray r)
{

    record rec;
    std::vector<std::pair<double, int>> intersect;
    if (!intersect_world(w, rec, r, intersect))
    {
        return color(0, 0, 0);
    }

    double index = -1;
    for (int i = 0; i < intersect.size(); i++)
    {
        if (intersect[i].first >= 0)
        {
            index = i;
            break;
        }
    }
    if (index==-1)
    {
        index=0;
    }
    //index=intersect.size()-1;
    std::cout << "I am from sphere  " << intersect[index].second << std::endl;
    comp com;
    com.prepare_computaion(w, r, index, intersect);
    
    color noshadow= shade_hit(w, com, w.groups[intersect[index].second]->m);
    return noshadow;
}

void render(camera cam, world w)
{
    int height = cam.hsize;
    int width = cam.vsize;
    canvas can(height, width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ray r = ray_for_pixel(cam, i, j, cam.transform);
            color c= colorat(w,r)*255;
             write_pixel(can,i,j, c);
        }
    }

    canvas2ppm(can, "gg.ppm");
}




int main()
{


   
    sphere middle=sphere(point(0,0,0),1);
    middle.set_transform(translation(-0.5,1,0.5));
    middle.m=material();
    middle.m.c=color(0.1, 1, 0.5);
    middle.m.diffuse=0.7;
    middle.m.specular =0.3;


    sphere right=sphere(point(0,0,0),1);
    right.set_transform(translation(1.5,0.5,-0.5)*scale(0.5,0.5,0.5));
    right.m=material();
    right.m.c=color(0.5, 1, 0.1);
    right.m.diffuse=0.7;
    right.m.specular =0.3;


    sphere left=sphere(point(0,0,0),1);
    left.set_transform(translation(-1.5,0.33,-0.75)*scale(0.3,0.3,0.3));
    left.m=material();
    left.m.c=color(1, 0.8, 0.1);
    left.m.diffuse=0.7;
    left.m.specular =0.3;

    plane p1=plane();
   // p1.set_transform(translation(0,0,-15));
    world w;
    w.groups.push_back(&middle);
    w.groups.push_back(&right);
    w.groups.push_back(&left);

   // wall set up;

    sphere floor=sphere(point(0,0,0),1);
    floor.set_transform(scale(10,0.01,10));
    floor.m=material();
    floor.m.c=color(1, 0.9, 0.9);
    floor.m.specular =0;
    double pi=3.1415926;
   

    sphere left_wall=sphere(point(0,0,0),1);
    left_wall.set_transform( translation(0,0,5)*rotation_y(-3.1415926/4)* rotation_x(3.1415926/2)*scale(10,0.01,10));
    left_wall.m=material();
    left_wall.m.c=color(1, 0.9, 0.9);
    left_wall.m.specular =0;
   



    sphere right_wall=sphere(point(0,0,0),1);
    right_wall.set_transform(translation(0,0,5)*rotation_y(3.1415926/4)* rotation_x(3.1415926/2)*scale(10,0.01,10));
    right_wall.m=material();
    right_wall.m.c=color(1, 0.9, 0.9);
    right_wall.m.specular =0;
   

    // w.l.position=point(1,3,0.8);
    tuple newdir=point(-10+0.5, 10-1, -10-0.5);

   // newdir=normalize(newdir)*2;
    //w.l.position=point(-1,1,-1);
   
   sphere lights=sphere(point(-1, 1, -1),0.2);
   lights.m.c=color(1,0,0);

    w.groups.push_back(& floor);
    w.groups.push_back(& left_wall);
    w.groups.push_back(& right_wall);
   // w.groups.push_back(& lights);






   // w.groups.push_back(&p1);
    camera cam(300,300, 3.1415926 /3);
    Matrix4d m = view_transform(point(0,1.5, -5), point(0, 1, 0), vector(0, 1, 0));
    //Matrix4d m = view_transform(point(0,0,0), point(0, 0, 1), vector(0, 1, 0));
    cam.transform=m;
    render(cam,w);




   

    return 0;
}
