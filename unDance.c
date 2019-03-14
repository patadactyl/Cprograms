
/***********************************************************************
 * Name(s)  Patrick Charlton                                           *
 * Box(s):  e189                                                       *
 * Assignment name: Uninterpretable Dance                               *
 *                                                                     *
 * Assignment for CS 451: Operating Systems and Concurrency             *
 ***********************************************************************/

/* *********************************************************************
 * Academic honesty certification:                                     *
 *   Written/online sources used:                                      *
 *      "Push It" by Salt-N-Pepa released in 1986 on the Album "Hot,   *
 *       Cool & Vicious"                                               *
 *       Creative ideas influenced by rand-beep.c and array-move.c     *
 *        written by Erik Opavsky and Dilan Ustek                      *
 *   Help obtained                                                     *
 *     Henry H. Walker                                                 *
 *   My/our signature(s) below confirms that the above list of sources *
 *   is complete AND that I/we have not talked to anyone else          *
 *   (e.g., CSC 161 students) about the solution to this problem       *
 *                                                                     *
 *   Signature:                                                        *
 ***********************************************************************/

#include <stdio.h>
#include "MyroC.h"
#include <stdlib.h> // for rand() and srand()
#include "scale-notes.h"
#include "eSpeakPackage.h"


//Robot will complete a little "shuffle" dance of back and forth movements at varying speeds
void shuffle(double speed[], double time[])
{
    printf("Everyday I'm Shufflin'\n");
    
    int i;
    int numMoves = 10;
    
    //Loops through and completes backward and forward movements for all 10 speed and time values in the arrays speed[] and time[]
    for (i = 0; i < numMoves; i++)
    {
        rBackward (speed[i], time[i]);
        rForward (speed[i], time[i]);
    }
}

//Robot will complete a spin move in a circle to the right for three seconds
void spinMove ()
{
    printf("I'm Spinning!\n");
    rTurnRight(.8, 3);
}

//Robot will go through a set sequence of movements and beeps
void spaz()
{
    printf("Oh no I'm spazzing out!\n");
    rTurnRight(0.8, 0.7);
    rBeep(0.75, pitchE5);
    rTurnRight(0.8, 0.3);
    rForward(0.5, 0.2);
    rBackward(0.7, 0.5);
    rTurnLeft(0.4, 0.3);
    rForward(0.8, 0.4);
    rBeep(0.5, pitchF5);
    rBeep(0.5, pitchF5);
}

//Robot will play the main melody from "Push It" by Salt 'N' Peppa
void pushIt()
{
    printf("Ahhh push it, PUSH IT REAL GOOD!\n");
    rBeep(0.6, pitchD5);
    rBeep(0.4, pitchA5);
    rBeep(0.4, pitchG5);
    rBeep(0.4, pitchF5);
    rBeep(0.4, pitchE5);
    rBeep(0.4, pitchC5);
    rBeep(0.2, pitchC5);
    rBeep(0.2, pitchE5);
    rBeep(0.2, pitchF5);
    rBeep(0.2, pitchE5);
    rBeep(0.2, pitchC5);
}

//Robot will complete a little "wiggle" dance of quick left and right turns
void wiggle(int i, int numMoves)
{
    printf("wiggle wiggle wiggle\n");
    numMoves = 6;
    
    //Loops through and completes alternating left and right turns for 6 speed and time values in the arrays speed[] and time[]
    for (i = 0; i < numMoves; i++)
    {
        rTurnRight(.8, .3);
        rTurnLeft(.8, .3);
    }

}

//Choose randomized move for robot to complete
void randomize(int * a, double speed[], double time[], int *i, int *numMoves)
{
    *a = rand() % 5; // generate a random, positive number from 0 to 4
    printf("Getting randome move *a = %d :", *a); //print value stored for a
    
    //switch
    switch (*a)
    {
        case 1: shuffle(speed, time);
            break;
        case 2: spinMove();
            break;
        case 3: spaz();
            break;
        case 4: pushIt();
            break;
        default: wiggle(*i, *numMoves);
            break;
    }
}

int
main()
{
    rConnect("/dev/rfcomm0");
    eSpeakConnect();
    
    //Needed to set variables here in main first
    int a;
    int i;
    int numMoves = 5;
    
    //Arrays speed and time used in shuffle function. Called in main to be recognized in both the shuffle and randomize functions
    double speed[] = {.8, .5, .4, 1, 1, 1, .8, .5, .7, .6};
    double time[] = {1, .8, .6, .1, .2, .2, .1, .3, .8, 4};
    
    //Selects 5 moves for the scribbler to complete in a randomized sequence
    for (i = 0; i < numMoves; i++)
    {
        randomize(&a, speed, time, &i, &numMoves);
    }
    
    eSpeakDisconnect();
    rDisconnect();
    
    return 0;
} // main


