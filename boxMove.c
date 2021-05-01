
/* * * * *
 * array-move.c
 *
 * Make the Scribbler move 5 times in the sequence:
 *    move forward for 1 second
 *    call the movement function with values 0.6, 1.0.
 *
 * Author: Patty wattty
 *
 * Date: 5 feb 2019
 */

#include <stdio.h>
#include "MyroC.h"
#include <stdlib.h> // for rand() and srand()


int numMoves = 5; // the number of moves that the Scribbler will do.
int i;
double speed[] = {.3, .2, .4, 1, 1, .3, .2, .5};
double time[] = {.3, 1, .6, .1, 1, .9, .3, .8};

//function boxMove makes scribbler move 5 times in specified sequence
void boxMove (void movement (double, double))
{
    movement (0.6, 1.0);
}

void spinMove ()
{
    boxMove (rTurnRight);
}

void shuffle ()
{
    for (i = 0; i < numMoves; i++)
    {
    rForward (speed[i], time[i]);
    rBackward (speed[i], time[i]);
    }
}

void spaz(int * a)
{
    *a = rand() % 6;
    if (*a = 0)
    { boxMove(rTurnLeft);
    } else if (*a = 1) {
        boxMove(rTurnRight);
    } else if (*a = 2){
        boxMove(rBackward);
    }
        else if (*a = 3) {
            boxMove(rForward);
        }
        else if (*a = 4) {
            shuffle();
        }
        else {
            spinMove();
        }
}


int
main()
{
    
    rConnect("/dev/rfcomm0");
    
    void (*moves[3]) (void) = {spinMove, shuffle, spaz};
    
    // move the scribbler in specified sequence
    for (i = 0; i < numMoves; i++)
    {
        moves[i];
    }
    
    // beep when done
    rBeep (1, 500);
    
    rDisconnect();
    
    return 0;
} // main
