/* A program stores n numbers, and
   computes their maximum, minimum, and average.
 * This code illustrates built-in C-style arrays.
 */
#include <stdio.h>

#define n 7  /* number of elements to be processed in array */

int main (void)
{    int j;
     int max, min, sum;

     printf ("Program to process real numbers.\n");

     /* declare array of n values  */
     int a[n] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};  

     /* print the values in the array */
     printf ("the values stored in array a are:\n");
     for (j = 0; j < n; j++)
       {
         printf ("   index:  %2d,     array value:  %2d\n", j, a[j]);
       }

     sum = max = min = a[0];    /* right to left assignment operator */

     for (j = 1; j < n; j++)
       { if (a[j] > max)
           max = a[j];     
         if (a[j] < min)
           min = a[j];
         sum += a[j];
       }

     printf ("Maximum:  %2d\n", max);
     printf ("Minimum:  %2d\n", min);
     printf ("Average:  %2d\n\n", sum/n);
     
     printf ("printing more array elements\n");
     for (j = -4; j < 14; j++)
       {
          printf ("a[%d] = %2d\n", j, a[j]);
       }

     return 0;
}
