#include <stdio.h>
#include "MyroC.h"

/* program to play a series of notes */

int main()
{

  rConnect ("/dev/rfcomm0");

  /* an array holds various musical notes */
  int notes[8] = {523, 587, 659, 698, 783, 880, 987, 1048};

  /* Since the array declaration supplies 8 numbers, this could also be declared
        int notes[] = {523, 587, 659, 698, 783, 880, 987, 1048};

     If array size is more than 8, more space is allocated, but only 
     the first part of the array is initialized:
        int notes[10] = {523, 587, 659, 698, 783, 880, 987, 1048};
  */

  printf ("play notes in array\n");
  int index;
  for (index = 0; index < 8; index++)
    {
      printf ("playing frequency %d\n", notes[index]);
      rBeep (0.5, notes[index]);
    }

  /* play a specified note */
  index = 5;
  printf ("note number %d is %d\n", index, notes[index]);
  rBeep (0.5, notes[index]);

  rDisconnect ();
  return 0;
}
