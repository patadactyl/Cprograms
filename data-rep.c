/* This allows the user to set a memory word to any desired bit patter,
   which may be specified either bit by bit, or by giving a decimal or 
   hexadecimal numeral designating an integer, or by giving a decimal
   numeral designating a float.  The bit pattern is then displayed in
   five different formats:  
       unsigned binary numeral, 
       unsigned hexadecimal numeral, 
       signed decimal numeral (as for int), and 
       floating-point decimal numeral (as for int).
       
   Programmer:  Henry Walker, Grinnell College
   Adapted for Sun Modula-2 by John Stone, grinnell College (Sept. 2, 1990)
   Rewritten in Pascal by Henry Walker (August 16, 1994)
   Rewritten in C by Henry Walker (August 29, 2001)
*/

#include <stdio.h>

union DATA {int integer; float real;};

typedef union DATA data;

void printBitGroups (data d, int bitGroups);

int main (void) {
  
  data d;
  char option;
  int toggleBit;

  d.integer = 0;

  printf ("\n");
  printf ("This program allows experimentation with the bit representations\n");
  printf ("  of integers and floating point numbers\n\n");

  while (1)
    {
      printf ("Menu Options\n");
      printf ("  0 - Set word to all zeros\n");
      printf ("  1 - Set word to all ones\n");
      printf ("  B - Toggle given bit\n");
      printf ("  F - Specify floating point number\n");
      printf ("  I - Specify integer\n");
      printf ("  Q - Quit\n");
      printf ("Enter option:  ");

      scanf(" %c", &option);

      switch (option)
        {case '0':
           d.integer = 0;
           break;
         case '1':
           d.integer = -1;
           break;
         case 'b':
         case 'B':
           printf ("  Enter which bit to toggle (31..0):  ");
           scanf ("%d", &toggleBit);
           d.integer = d.integer ^ (1 << toggleBit);
           break;
         case 'f':
         case 'F':
           printf ("  Enter real number:  ");
           scanf ("%f", &d.real);
           break;
         case 'i':
         case 'I':
           printf ("  Enter integer:  ");
           scanf ("%d", &d.integer);
           break;
         case 'q':
         case 'Q':
           printf ("Program terminated\n");
           return 0;
           break;
         case 's':
         case 'S':

           break;
        default: printf ("Unrecognized option -- please try again\n");
          continue;
        }
      printf ("\n");
      printf ("     Binary Form:  ");
          printBitGroups (d, 1);
      printf ("Hexadecimal Form:  ");
          printBitGroups (d, 4);
      printf ("    Integer Form:  %d\n", d.integer);
      printf ("      Float Form:  %15.10f\n\n", d.real);

    }

}


void printBitGroups (data d, int bitGroups) {
  int value = d.integer;
  int mask = 0;
  int iterations = 32 / bitGroups;
  int a[iterations];
  int i;

  for (i = 0; i < bitGroups; i++) {
    mask = 1 + (mask << 1);
  }

  for (i = 0; i < iterations; i++){
    a[i] = value & mask;
    value = value >> bitGroups;
  }

  for (i = iterations-1; i >= 0; i--) 
    printf ("%X", a[i]);
  printf ("\n");
}
