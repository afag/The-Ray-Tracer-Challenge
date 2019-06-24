#include "tuple.h"
#include "color.h"
#include "canvas.h"
#include "matrix.h"
#include "transformation.h"
#include "ray.h"
#include "sphere.h"
#include "light.h"

color lightning(material m, light l, tuple pos, tuple eye, tuple normal)
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
    // check whether light normal is on the other side of the surface;
    double light_dot_normal = dot(lightv, normal);
    if (light_dot_normal < 0)
    {
        return res;
    }

    else
    {
        color diffuse = effective_color * m.diffuse * light_dot_normal;
        res=res+diffuse;
    }
    
    tuple reflectv=reflect(-lightv, normal);
    double reflect_dot_eye=dot(reflectv,eye);

   if (reflect_dot_eye<=0){
       return res;
   }

   else{
       double factor=pow(reflect_dot_eye,m.shininess);
       color specular=l.intensity*m.specular*factor;
       



       return res+specular;
   }




}
int main()
{
    canvas can(500,500);
    sphere s(point(250, 250, 0), 100);
    s.m=material();// add material
    s.m.c=color(1,0.2,1);
    // add light
    light l(point(250,150,150), color(1,1,1));
    for (int i=0;i<500;i++){
        for(int j=0;j<500;j++){
        record rec;
        tuple direction=vector(i-250,j-250,-150);
         ray r(point(250, 250, 150), direction);
         if (s.hit(r, rec, -100000, 1000000)){
             tuple pos=rec.p;
             tuple eye=-r.direction/r.direction.magnitude();
             color c=lightning(s.m,l,pos,eye, rec.normal);

             //std::cout<<"magnitude: "<<rec.normal.magnitude()<<std::endl;
             c=c*255;
             //std::cout<<c;
              write_pixel(can,i,j, c);
         }
          

        }
    }
    canvas2ppm(can, "clock.ppm");

   
    return 0;
}
