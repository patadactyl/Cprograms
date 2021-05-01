/* Practice using procedures and parameters in C
   Program 1
*/

#include <stdio.h>

void pr (int a, int *b) 
{  printf ("pr 1  :  a =%2u; b =%2u\n", a, b);

   a = 5;
   b = 6;

   printf ("pr 2  :  a =%2u; b =%2u\n", a, b);
}


int main (void) 
{  int x = 3;
   int y = 4;

   printf ("practice program 1\n");
   printf ("main 1:  x =%2u; y =%2u\n", x, y);

   pr (x, y);

   printf ("main 2:  x =%2u; y =%2u\n", x, y);
   return 0;
}
