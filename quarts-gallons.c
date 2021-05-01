/* A program to convert a number of gallons and quarts to liters
*/

#include <stdio.h>

int main ()
  {  printf ("This program converts a number of gallons and quarts to liters\n");  

   int gallons, quarts; 
   double liters;

    printf ("Enter integers for gallons and quarts:  ");
    scanf ("%d %d", &gallons, &quarts);
    liters = (4*gallons + quarts) / 1.056710 ;

    printf ("%d gallons, %d quarts = %lf liters\n", gallons, quarts, liters);

    return 0;
  }
