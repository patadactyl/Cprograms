/* * * * *
 * array-move.c
 *
 * Make the Scribbler move in different speeds and times by putting different numbers to different
 * arrays and giving them as parameters to the commands rForward and rTurn.
 *
 * Authors: Dilan Ustek, Erik Opavsky
 *
 * Date: 8 July 2011
 */


#include "MyroC.h"

int
main()
{
    
    rConnect("/dev/rfcomm0");
    
    int numMoves = 8; // the number of moves that the Scribbler will do.
    int i;
    
    // the various speeds and times in two seperate arrays
    
    double speed[] = {.3, .2, .4, 1, 1, .3, .2, .5};
    
    double time[] = {.3, 1, .6, .1, 1, .9, .3, .8};
    
    // go forward and turn for the various speeds and times given by the two arrays
    for (i = 0; i < numMoves; i++)
    {
        rForward (speed[i], time[i]);
        rTurnRight (speed[i], time[i]);
    }
    
    // beep when done
    rBeep (1, 500);
    
    rDisconnect();
    
    return 0;
} // main
