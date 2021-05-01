/* Practice using procedures and parameters in C
 Program 3
 */

#include <stdio.h>

void prA (int *r, int s)
{  printf ("prA 1 :  r =%2u;s =%2u\n", *r, s);
    
    *r = 5;
    s = 6;
    
    printf ("prA 2 :  r =%2u;s =%2u\n", *r, s);
}


void prB (int a, int *b)
{  printf ("prB 1 :  a =%2u;b =%2u\n", a, b);
    
    prA (&a, b);
    
    printf ("prB 2 :  a =%2u;b =%2u\n", a, b);
}


int main (void)
{  int x = 3;
    int y = 4;
    
    printf ("practice program 3\n");
    printf ("main 1:  x =%2u; y =%2u\n", x, y);
    
    prB (x, &y);
    
    printf ("main 2:  x =%2u; y =%2u\n", x, y);
    return 0;
}
