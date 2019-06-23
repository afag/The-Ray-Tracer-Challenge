#include"tuple.h"
#include"color.h"
#include"canvas.h"
#include"matrix.h"
#include"transformation.h"

int main()
{
    //Matrix4d trans=translation(5,-3,2);
    //tuple re=trans.inverse()*tuple(-3,4,5,1);
    //std::cout<<re<<std::endl;

   // Matrix4d sc=scale(2,3,4);
    //std::cout<<sc.inverse()*tuple(-4,6,8,1);


//Matrix4d x=rotation_z(3.1415926/2);
//std::cout<<x;


canvas can(100,100);

tuple t(0,20,0,1);
for(int i=0;i<12;i++){
   double radian=3.1415926*i/6;
   Matrix4d rotate=rotation_z(radian);
   tuple ts=rotate*t;
   int x=50+ts.x;  // set origin to be (50,50);
   int y=50+ts.y;
   write_pixel(can,x,y, color(255,255,255));
   
}
canvas2ppm(can, "clock.ppm");
    return 0;
}