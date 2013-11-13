//Compile with: g++ -O3 -o Backbone_Algorithm ~/Backbone_Algorithm.cpp

#include <math.h>
#include <float.h>
#include <iostream>
#include <iomanip>

//These constants determine the range for the x-values.
const float x_begin = -32767.0f;
const float x_end = 32767.0f;

//Type the equation into this function. "powf" is "power_floating_point" for floats.
//For list of functions, see http://www.cplusplus.com/reference/cmath/
inline float equation(float x)
{
	return powf(x, 2.0f)-4.0f;
}

using namespace std;

int main ()
{        
    std::cout.precision(20);
    std::cout.setf( std::ios::fixed, std::ios::floatfield ); // floatfield set to fixed
    
    const float max = FLT_MAX;
    const float mm = 0.00024414062f;

    float h= x_begin;
    float j= powf (h, 2.0f)-4.0f;

    float k= (j < 0.0f) ? (-j) : j ;

    float b;
    float c;
    float l;
    bool hasSolution = false;
    cout << '\n' << "Solutions: " << '\n';
    for(b = nextafterf(h,max);b < -0.0078125f; b = nextafterf(b,max) )
    {     
        c = equation(b);
        l = (c < 0.0f) ? (-c) : c ;
        if( k < mm )
        {
                if( (l>=k) && (hasSolution == false) )
                {
                        std::cout << h << '\n';
                        hasSolution = true;
                }
        }
        else {hasSolution = false;}
        k=l;
        j=c;
        h=b;
    }

hasSolution = false;
h = 0.0f;
j = equation(h);
k = (j < 0.0f) ? (-j) : j ;

    for(b = 0.0078125f; b < x_end; b = nextafterf(b,max) )
    {
        c = equation(b);
        l = (c < 0.0f) ? (-c) : c ;

        if( k < mm )
        {
                if( (l>=k) && (hasSolution == false) )
                {
                        std::cout << h << '\n';
                        hasSolution = true;
                }
        }
        else {hasSolution = false;}
        k=l;
        j=c;
        h=b;
    }
cout << '\n';
return 0;
}
