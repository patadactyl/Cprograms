/* A simple program to convert a number of quarts to liters
*/

#include <stdio.h>                  /* reference to standard I/O library */

int main ()                         /* beginning of main program */
{
   printf ("This program converts a number of quarts, gallons, or pints to liters\n");  
                                    /* write opening statement */

  /* declaration of variables, with their types */
   int quarts;                      /* int means integer (no decimal point) */
   int gallons;
   int pints;
   double liters;                   /* double means real number */

   gallons = 3;
   quarts = 2;                      /* specify the number of quarts as 2 */
   pints = 1;

   liters = quarts / 1.056710;     /* arithmetic and assignment */
   quarts = gallons * 4;
   gallons = pints / 8;

   printf ("%d quarts = %lf liters\n", quarts, liters);
   printf ("%d gallons = %lf liters\n", gallons, liters);
   printf ("%d pints = %lf liters\n", pints, liters);

                                    /* write text and new line */

   return 0;                        /* the program ran without errors */
}