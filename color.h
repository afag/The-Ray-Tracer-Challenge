#ifndef COLORH
#define COLORH

class color{

    public:
    color(){
        r=0;
        g=0;
        b=0;
    }
    color (float r, float g, float b):r(r),g(g),b(b){}
    float r;
    float g;
    float b;
    
    color operator +(color c){
        return color(r+c.r, g+c.g,b+c.b);
    }
    color operator -(color c){
        return color (r-c.r, g-c.g,b-c.b);
    }
    color operator *(float a){
        return color(a*r, a*g,a*b);
    }

    color operator*(color c){
        return color (r*c.r, g*c.g, b*c.b);
    }
    

};

inline std::ostream &operator<<(std::ostream &os, const color &t)
{
    os << t.r << " " << t.g << " " << t.b << std::endl;
    ;
    return os;
}

inline color operator * (float a, color c){
    return color (a*c.r, a*c.g, a*c.b);
}


#endif