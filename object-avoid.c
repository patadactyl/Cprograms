/* * * * *
 * object-avoid.c
 *
 * Scribbler moves around avoidig objects. It turns to the side that does not
 * have an object, or turns around if only obstacles are found with sensors.
 *
 * The program uses 800 as a threshold for obstacle being seen using 
 * rGetObstacle.
 *
 * Authors: April O'Neill, Dilan Ustek
 * revised for module 2 by: Dilan Ustek
 *
 * Date: 7 July 2011
 *
 * Minor editing by Henry M. Walker:  22 September 2013
 */

#include "MyroC.h"

#define MAX_ITERATIONS 60 // move for a specific number of iterations

int 
main()
{
  rConnect ("/dev/rfcomm0");  
  rSetForwardnessTxt ("fluke-forward");

  int array[3]; /* array to be given to rGetObstacleAll to store all 3 values */
  int i;
 
  // loop to move avoiding obstacles for a specified number of iterations
  for (i=0; i <= MAX_ITERATIONS; i++)
    {
      rGetObstacleAll (array);

      // If no object seen, move forward
      if ( array[0] < 800 && array[1] < 800 && array[2] < 800)
        rMotors (1,1);

      // If object seen on left only, turn right
      if (array[0 ]> array[2] < 800)
        rTurnRight (1,0.5);

      // If object seen only in middle, turn right
      if (array[0 ]< 800 && array[1] > 800 && array[2] < 800)
        rTurnRight (1,0.5);

      // If object seen only on right, turn left
      if (array[0 ]< array[2] > 800)
        rTurnLeft (1,0.5);

      // Else turn around
      else 
        {
          rBeep (1,600);
          rTurnRight (1,2);
        }
    } // End of loop

  rDisconnect();

  return 0;
} // main
