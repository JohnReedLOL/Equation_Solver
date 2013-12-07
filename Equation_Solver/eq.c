#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>




int main ()
{
  char my_string [110];
  int line_counter;
  int i;
  FILE * eq_helper;
  printf ("Use C \"math.h\" functions such as pow(x,y) and sin(x) to enter an equation into the solver: ");
  if(!gets (my_string)) {perror("Failed to get line."); return 1;}


  eq_helper = fopen( "eq_helper.c" , "r+");
  line_counter = 1;


if ( eq_helper != 0 )
{
char line [ 1024 ]; /* or other suitable maximum line size */


while ( ( fgets(line, 1024, eq_helper) )  && (line_counter < 25 ) )
{
    ++line_counter;
}
if( line_counter == 25 )
{
    fputs( my_string, eq_helper );
    printf("input success. \n");
    fclose ( eq_helper );
        ++line_counter;
}
}
else
{
  perror("Cannot access file eq_helper.c in my current folder");
  return 1;
}

assert (line_counter == 26);


printf ("Checking if processor is available...");
if ( system(0) ) puts ("Ok");
else exit (EXIT_FAILURE);
printf ("Gcc is compiling your equation...\n");
i=system ("gcc -march=native -Ofast -Wall -Wextra -pedantic -Werror ./eq_helper.c -o helper_function");
if (i==0) 
{
        printf("gcc compilation returned successful.\n");
        i= system("./helper_function");
        if (i==0) { printf("success!\n"); return 0;}
        else {perror("helper function process returned an error code"); return 1;}
}
else
{
        printf("gcc compilation returned an error code.");
        return 1;
}
return 0;
}
