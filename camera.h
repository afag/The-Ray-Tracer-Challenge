#ifndef CAMEARH
#define CAMEARH
#include"matrix.h"
#include"ray.h"
class camera{ // generate ray


    public:
    
    camera(double hsize, double vsize, double field_of_view): hsize(hsize),vsize(vsize), field_of_view(field_of_view){

        double data[16]={1,0,0,0, 0,1,0,0, 0,0,1,0,    0,0,0,1};
        transform=Matrix4d(data);
    };

    double hsize;
    double vsize;

    double field_of_view;
    double half_width;
    double half_height;
    double pixel_size;
    Matrix4d transform; 

};

ray ray_for_pixel(camera cam,int px, int py, Matrix4d view_matrix)
{

    double half_view=tan(cam.field_of_view/2);
    double aspect=cam.hsize/cam.vsize;

    if (aspect>=1){
        cam.half_width=half_view;
        cam.half_height=half_view/aspect;
    }

    else{
         cam.half_width=half_view*aspect;
        cam.half_height=half_view;
    }

     cam.pixel_size=(cam.half_width*2)/cam.hsize;

    double xoffset=(px+0.5)*cam.pixel_size;
    double  yoffset=(py+0.5)*cam.pixel_size;

    double  world_x=cam.half_width-xoffset;
    double  world_y=cam.half_height-yoffset;
    std::cout<<cam.half_width<<" "<<cam.half_height<<std::endl;
    tuple pixel=view_matrix.inverse()*point (world_x, world_y,-1);
    tuple origin=view_matrix.inverse()*point (0, 0,0);
    std::cout<<"camera origin:......................................................................."<<origin;
    tuple dir=pixel-origin;
    dir=normalize(dir);
    ray r(origin,dir);
    return r;
}




#endif