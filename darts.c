/*  This program approximates Pi by picking a points in a sqaure and   *
 *  and determining how often they are also in an appropriate circle.  */

#include <stdio.h>

/* libraries for the random number generator */
#include <stdlib.h>
#include <time.h>

/* Within the stdlib.h library,
 *    time returns a value based upon the time of day
 *    on some machines, rand returns a random integer between 0 and 2^31 - 1
 *        although on some machines rand gives values between 0 and 2^32 - 1
 *        and on other machines rand gives values between 0 and 2^15 - 1
 *    MaxRandInt is this maximum integer minus 1
 *        (Note:  2^32 = 2147483648, 2^31 = 1073741824 and 2^15 = 32768)
 *    Use 2^32-1 for SparkStations
 *    Use RAND_MAX for Linux machines, 
 *    Use 2^15-1 for IBM Xstation 140s and HP 712/60s
 */
const int MaxRandInt = RAND_MAX;       /* declaration of program constants*/
const int NumberOfTrials = 5000;

int main (void)
{  int i;
   int counter = 0;                      /* declare and initialize counter */
   double x, y;
   double MaxRandReal = (double) MaxRandInt; /* make MaxRandInt a real */

   printf ("This program approximates Pi by picking %d points in a square\n", 
            NumberOfTrials);
   printf ("and counting the number in an appropriate circle.\n\n");

   // initialize random number generator
   // change the seed to the random number generator, based on the time of day
   srand (time ((time_t *) 0) );

   // pick points in first quadrant with coordinates between 0 and 1
   // determine how many are in the circle of radius 1
   for (i = 1; i <= NumberOfTrials; i++) {
       x = rand() / MaxRandReal;
       y = rand() / MaxRandReal;
       if (x*x + y*y <= 1) counter++;
   }

   printf ("%d points were inside the circle, and\n", counter);
   printf ("the approximate value of Pi is %.5f .\n",
                4.0 * counter / NumberOfTrials);
   return 0;
}
