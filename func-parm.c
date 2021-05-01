#include <stdio.h>

/* program to print tables of metric equivalents */

/* function to convert gallons and pints to liters */
double toLiters (double gal, double pts)
{
  return (gal*4.0 + pts/2.0)/ 1.056710;
}

/* fucntion to convert feet and inches to centimeters */
double toCenti (double feet, double in)
{
  /* according to the National Bureau of Standards, 
     effective July 1, 1959, an inch was defined as exactly 2.54 centimeters */
  return (12.0*feet + in) * 2.54;
}


/* function to print a table of metric equivalents */
void printTable (double func (double, double))
{
  double row, col;
  double rowStart = 0.0;
  double rowEnd  = 10.0;
  double colStart = 0.0;
  double colEnd  = 10.0;

  /* print column titles */
  printf ("         ");  /* space at start of row */
  for (col = colStart; col <= colEnd; col++)
    {
      printf (" %5.1lf", col);
    }
  printf ("\n\n");

  /* iterate over series of rows */
  for (row = rowStart; row <= rowEnd; row++)
    {
      /* print row label */
      printf ("  %4.1lf   ", row);

      /* print table entries */
      for (col = colStart; col <= colEnd; col++)
        {
          printf (" %5.1lf", func (row, col));
        }

      /* end of row */
      printf ("\n");
    }


}

int main ()
{
  printf ("Table of gallon/pint to liter equivalents\n");
  printTable (toLiters);

  printf ("\n\nTable of feet/inch to centimenter equivalents\n");
  printTable (toCenti); 

 return 0;
}

