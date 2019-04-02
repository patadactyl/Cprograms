/* Approximating area under x^2 on [1, 3] using the Trapezoidal Rule.*
 * using a function to perform the area computation.                     */

#include <stdio.h>

double f(double x);     
/* function to be used in the area approximation */

double area_l_to_r(double a, double b, int n);
/* Approximation of area under f(x) on [a, b] using the Trapezoidal Rule measured from left to right */

double area_r_to_l(double b, double a, int n);
/* Approximation of area under f(x) on [a, b] using the Trapezoidal Rule measured from right to left */

int main (void)
{  int n;
   printf ("Program approximates the area under a function using the ");
   printf ("Trapezoidal Rule.\n");

   /* print table titles */
   printf ("    Number         Approximate Area         Approximate Area\n");
   printf ("  Intervals         Computed L to R         Computed R to L\n");
   
   /* printf body of table */
   for (n = 100; n <= 1000000000; n *= 10)
     {
       printf ("%11d  %23.15lf  %23.15lf\n", n, area_l_to_r(1.0, 3.0, n), area_r_to_l(3.0, 1.0, n));
     }

   return 0;
}

double f(double x) 
/* function to be used in the area approximation */
{  
  return x*x;
}
 
double area_l_to_r (double a, double b, int n)
/* Finding area via the Trapezoidal Rule, computing terms from 
   left to right (i.e., first to last)
*/
{  int i;
   double width = (b - a) / n; 
   double sum = f(a) / 2.0;   /* first term in sum */
   double xvalue;

   /* add middle terms */
   for (i = 1; i < n; i++)
     {
       xvalue =  a + i*width;
       sum += f(xvalue);
     }

   /* add last term */
   sum += f(b) / 2.0;

   return (sum * width);
}

double area_r_to_l (double b, double a, int n)
/* Finding area via the Trapezoidal Rule, computing terms from
 left to right (i.e., first to last)
 */
{   int i;
    double width = (b - a) / n;
    double sum = f(a) / 2.0;   /* first term in sum */
    double xvalue;
    
    /* add middle terms */
    for (i = n; i > 1; i--)
    {
        xvalue =  a + i*width;
        sum += f(xvalue);
    }
    
    /* add last term */
    sum += f(b) / 2.0;
    
    return (sum * width);
}
