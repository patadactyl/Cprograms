/*
 * rand-beep.c
 *
 * Author: Erik Opavsky
 *
 * Date: 28 July, 2011
 */

#include "MyroC.h"
#include <stdlib.h> // for rand() and srand()
#include <time.h>   // for time()
#include <stdio.h>  // for printf()

// perform a randomized beep
void
randBeep (int * a)
{
  *a = rand() % 6; // generate a random number from 0 to 5
  printf ("*a = %d\n", *a); // print value stored ad *a
  rBeep (((*a) + 1)/2.0, (400 + 50 * (*a))); // beep for a + 1 seconds at 400 + (50 * a) hz
} // randBeep


int
main()
{
  rConnect ("/dev/rfcomm0");
  int i;

  srand (time (NULL)); // necessary so different random numbers every time

  do
    {
      randBeep (&i);
    } while (i < 5); // stop if i is 5 or higher

  printf ("i has a value of %d.  Program terminating.\n", i);

  rDisconnect();
  return 0;
} // main
