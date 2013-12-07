#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846f
#define e 2.71828182845904523536f
#define pow(x,exponent) powf((x),(exponent))
#define sqrt(x) sqrtf((x))
#define sin(x) sinf((x))
#define cos(x) cosf((x))
#define tan(x) tanf((x))
#define asin(x) asinf((x))
#define acos(x) acosf((x))
#define atan(x) atanf((x))
#define atan2(numerator,denominator) atan2f((numerator),(denominator))
#define exp(x) expf((x)) 
#define ldexp(x, exponentPow2) ldexpf((x),(exponentPow2)) 
#define log(xBaseE) logf((xBaseE)) 
#define log10(x) log10f((x))
#define ceil(x) ceilf((x))
#define floor(x) floorf((x))
#define fmod(Xfloat,divisor) fmodf((Xfloat),(divisor))
#define abs(x) fabsf((x))


#define THE_EQUATION(x) \
pow(x,2.0f)-1.0f                                                                                                                                        
                                                                                                                                                        

/* Search breadth */
#define X_BEGIN -32767.0f
#define X_END 32767.0f


/* Closest search point to zero along the x axis. */
#define LEFT_PROXIMITY -0.0078125f
#define RIGHT_PROXIMITY 0.0078125f


/* Increase zero threshold for rough approximations. */
#define THRESHOLD 0.00024414062f


/* Increase step size to trade precision for speed */
#define STEP_SIZE 1


union bit_twiddler {
float f;
int i;
};


int main ()
{
   int hasSolution; /*bool*/
   union bit_twiddler x1;
   union bit_twiddler y1;
   union bit_twiddler x2;
   union bit_twiddler y2;


   hasSolution = 0;
   x1.f = X_BEGIN;
   y1.f = THE_EQUATION( (x1.f) );
   if (y1.f < 0.0f) y1.f = -y1.f;
  
   x2.f = x1.f;
   printf("Negative zeros: \n");
   for(x2.i -= STEP_SIZE; x2.f < LEFT_PROXIMITY; x2.i -= STEP_SIZE  )
   {
       y2.f = THE_EQUATION( (x2.f) );
       if (y2.f < 0.0f) y2.f = -y2.f;

       if( y1.f > THRESHOLD )
           hasSolution = 0;
       else
       {  
           if( (y2.f >= y1.f) && (hasSolution == 0) )
           {
                   printf("%g \n", x1.f);
                   hasSolution = 1; 
           }
       }
   y1.f = y2.f;
   x1.f = x2.f;
   }

hasSolution = 0; 
x1.f = 0.0f;
y1.f = THE_EQUATION( (x1.f) );
if (y1.f < 0.0f) y1.f = -y1.f;
printf("Positive zeros: \n");

   for(x2.f = RIGHT_PROXIMITY; x2.f < X_END; x2.i += STEP_SIZE  )
   {
       y2.f = THE_EQUATION( (x2.f) );
       if (y2.f < 0.0f) y2.f = -y2.f;

       if( y1.f > THRESHOLD )
           hasSolution = 0;
       else
       {  
           if( (y2.f >= y1.f) && (hasSolution == 0) )
           {
                   printf("%g \n", x1.f);
                   hasSolution = 1; 
           }
       }
   y1.f = y2.f;
   x1.f = x2.f;
   }
printf("Done searching for zeros. \n");
return 0;
}
