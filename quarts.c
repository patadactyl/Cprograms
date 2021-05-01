/* A simple program to convert a number of quarts to liters
*/

#include <stdio.h>                  /* reference to standard I/O library */

int main ()                         /* beginning of main program */
{
   printf ("This program converts a number of quarts to liters\n");  
                                    /* write opening statement */

  /* declaration of variables, with their types */
   int quarts;                      /* int means integer (no decimal point) */
   double liters;                   /* double means real number */

   quarts = 2;                      /* specify the number of quarts as 2 */

   liters = quarts / 1.056710;     /* arithmetic and assignment */

   printf ("%d quarts = %lf liters\n", quarts, liters);
                                    /* write text and new line */

   return 0;                        /* the program ran without errors */
}
