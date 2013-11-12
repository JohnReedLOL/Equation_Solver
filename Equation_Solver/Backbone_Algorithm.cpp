//Compile with: g++ -std=c++11 -O3 -o Backbone_Algorithm ~/Backbone_Algorithm.cpp

#include <cmath> 
#include <float.h>  
#include <iostream>
#include <iomanip>

using namespace std;

//Type the equation into this function.
inline float equation(float x)
{
//For example, the equation pow(x,2)-4=0 has solutions +-2.
return powf(x, 2.0f)-4.0f; 
}

int main ()
{	
    std::cout.precision(30);
    std::cout.setf( std::ios::fixed, std::ios::floatfield ); // floatfield set to fixed
    
    //const float c = 32767.0f;
    
    const float max = FLT_MAX;
    const float mm = 0.00024414062f;

    //const float diff = 0.0f + 8.0f*nextafterf(0.0f,max);

    float h= -32767.0f;
    float j= powf (h, 2.0f)-4.0f;

    float k= abs(j);

    float b;
    float c;
    float l;
    bool hasSolution = false;
	cout << '\n';
    for(b = nextafterf(h,max);b < -0.0078125f; b = nextafterf(b,max) )
    {
	//c= powf(b, 2.0f)-4.0f; //The equation.	
	c = equation(b);
	l = abs(c);
	if( k < mm )
	{
		if( (l>=k) && (hasSolution == false) )
		{
			std::cout << "+Solution: " << h << '\n' << "+Distance to x-axis: " << k << '\n' << '\n';
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
//j = powf(h, 2.0f)-4.0f; //The equation.
j = equation(h);
k = abs(j);

    for(b = 0.0078125f; b < 32767.0f; b = nextafterf(b,max) )
    {
	//c= powf(b, 2.0f)-4.0f; //The equation.
	c = equation(b);
	l = abs(c);

	if( k < mm )
	{
		if( (l>=k) && (hasSolution == false) )
		{
			std::cout << "-Solution: " << h << '\n' << "-Distance to x-axis: " << k << '\n' << '\n';
			hasSolution = true;
		}
	}
	else {hasSolution = false;}
	k=l;
	j=c;
	h=b;
    }

  return 0;
}
