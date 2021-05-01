/* This allows the user to set or modify short and long integers and then 
   examine the results in both decimal and binary format.  
       
   Programmer:  Henry Walker, Grinnell College
   Written in C by Henry Walker (January 28, 2005)
   Last revised by Henry Walker (January 30, 2005)
*/

#include <stdio.h>

void print_binary(int digits, int number);

int main (void) {
  
  short short_int = 1;
  int   inte = 1;
  int number;
  char option;

  printf ("\n");
  printf ("This program allows experimentation with different sizes of integers\n\n");
  printf ("Initial integer values:           decimal                       binary\n");
  printf ("   Short (16-bit) integer:%13hd                   ", short_int);
  print_binary (16, short_int);
  printf ("\n");
  printf (" Regular (32-bit) integer:%13d   ", inte);
  print_binary (32, inte);
  printf ("\n\n");

  while (1) 
    {
      printf ("Menu Options\n");
      printf ("  I - initialize each number to a value you have entered\n");
      printf ("  A - add 1 to each integer\n");
      printf ("  S - subtract 1 from each number\n");
      printf ("  M - multiple each number by 2\n");
      printf ("  D - divide each number by 2\n");
      printf ("  Q - Quit\n");
      printf ("Enter option:  ");
      scanf(" %c", &option);

      switch (option)
        {
        case 'i':
        case 'I':
          printf ("   Enter value that will be assigned to each integer:  ");
          scanf ("%d", &number);
          short_int = (short) number;
          inte      = number;
          break;
        case 'a':
        case 'A':
          short_int += (short) 1;
          inte      += 1;
          break;
        case 's':
        case 'S':
          short_int -= (short) 1;
          inte      -= 1;
          break;
        case 'm':
        case 'M':
          short_int *= (short) 2;
          inte      *= 2;
          break;
        case 'd':
        case 'D':
          short_int /= (short) 2;
          inte      /= 2;
          break;
        case 'q':
        case 'Q':
          printf ("Program terminated\n");
          return 0;
          break;
        default: printf ("Unrecognized option -- please try again\n");
          continue;
        }
      printf ("Resulting integer values          decimal                       binary\n");
      printf ("   Short (16-bit) integer:%13hd                   ", short_int);
      print_binary (16, short_int);
      printf ("\n");
      printf (" Regular (32-bit) integer:%13d   ", inte);
      print_binary (32, inte);
      printf ("\n\n");

    }

}

void print_binary(int digits, int number) {
  /* this function prints the bit representation of number, 
     assuming that digits gives the number of bits in the original 
     declaration of number.
  
     when called with short ints, 
          digits should be 15 (at least on Intel i7 machines)
     when called with regular ints, 
          digits should be 32
  */

  int a[digits];
  int i;
  int mask = 1;

  for (i = 0; i < digits; i++){
    a[i] = number & mask;
    number = number >> 1;
  }

  for (i = digits-1; i >= 0; i--)
    printf ("%X", a[i]);




}
