/***************************************************************************
     * Name(s)  Dilan Ustek and April O'Neill                              *
     *          Editing by Henry M. Walker                                 *
     * Box(s):  Science Division Office Mailbox                            *
     * Assignment name  Demonstration program for Module 000               *
     * Assignment Used in class January 2015, January 2017, September 2017 *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *     folk tradition with a long history                              *
     *        for example, see                                             *
     *            http://en.wikipedia.org/wiki/Do_Your_Ears_Hang_Low%3F    *
     *     Google search for "ears hang low" yields over 6,000,000 hits    *
     *   Help obtained                                                     *
     *     MyroC development team, including Erik Opavsky and David Cowden *
     *   My/our signature(s) below confirms that the above list of sources *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 134 students) about the solution to this problem       *
     *                                                                     *
     *   Signature:                                                        *
     ***********************************************************************/

/* Annotated program for Scribbler beeping "Do Your Ears Hang Low"
 */

#include <stdio.h>
#include "MyroC.h"
#include "eSpeakPackage.h"

/* compile with the line
   make scribbler-espeak
*/

/* song from ears-hang-low.c 
 */

/* Musical notes in the scale, as they correspond to beep frequency*/
/* const is a constant variable. It needs to be initiated when it's 
   declared because they will not be altered.
   int is an integer.*/
const int pitchA4  = 440;
const int pitchBf4 = 466;
const int pitchAs4 = 466; 
const int pitchB4  = 493;
const int pitchC5  = 523;
const int pitchDf5 = 554;
const int pitchCs5 = 554; 
const int pitchD5  = 587;
const int pitchEf5 = 622;
const int pitchDs5 = 622;
const int pitchE5  = 659;
const int pitchF5  = 698;
const int pitchGf5 = 739;
const int pitchFs5 = 739; 
const int pitchG5  = 783;
const int pitchAf5 = 830;
const int pitchGs5 = 830;
const int pitchA5  = 880;
const int pitchBf5 = 932;
const int pitchAs5 = 932;
const int pitchB5  = 987;

/* program to control a Scribbler 2 robot, so that 
      * the robot moves, while playing a song
      * the workstation provides commentary on the progress
          of program execution
   pre-condition:  Scribbler 2 robot is turned on with fresh batteries
   post-condition: song and movement completed
*/
   
int main ()
{
  printf ("program to make the Scribbler robot move and beep\n");

  /* initialize both the robot and eSpeak */
  rConnect ("/dev/rfcomm0");
  //rConnect ("0950");            /* connect to markov robot */
  eSpeakConnect();

  /* Move left and right, with associated beeps */
  printf ("turning to the right\n");
  eSpeakTalk ("Turn right and beep");
  rTurnRight (0.5, 1.0);  /* turn right at half speed for 1 second */
  rBeep (1.0, 880);       /* beep a middle C for 1 second */

  /* Move forward and backward */
  printf ("moving forward and backward\n");
  eSpeakTalk ("Move forward and backward");
  rForward (1.0, 1.0);
  rBackward (1.0, 1.0);

  /* Move left and right, with associated beeps */
  printf ("turning to the left\n");
  eSpeakTalk ("Turn left and beep");
  rTurnLeft (0.75, 1.0);  /* turn left at 3/4 speed for 1 second */
  rBeep (1.0, 1760);      /* beep an octive above middle C for 1 second */

  /* circle right */
  printf ("circle right\n");
  eSpeakSetGender ("male");
  eSpeakTalk ("circle right");
  rMotors (0.75, 0.25);
  
  /* Now beep the song! */

  /* line 1: "Do your ears hang low?" */
  /* robot beeps with the pitch A5 (references to 880 Hz.) for 0.25 seconds. */
  rBeep (0.25, pitchB5); 
  rBeep (0.25, pitchA5);
  rBeep (0.5, pitchG5);
  rBeep (0.5, pitchG5);
  rBeep (0.5, pitchG5);

  /* line 2: "Do they wobble to and fro?" */
  rBeep (0.25, pitchB4);
  rBeep (0.25, pitchC5);
  rBeep (0.20, pitchD5);
  rBeep (0.20, pitchE5);
  rBeep (0.20, pitchD5);
  rBeep (0.20, pitchB4);
  rBeep (0.40, pitchD5);
 
  /* line 3: "Can you tie them in a knot?" */ 
  rBeep (0.25, pitchG5);
  rBeep (0.25, pitchA5);
  rBeep (0.20, pitchB5);
  rBeep (0.20, pitchB5);
  rBeep (0.20, pitchB5);
  rBeep (0.20, pitchB5);
  rBeep (0.50, pitchB5);

  rMotors (0.0, 0.0);

  /* circle left */
  printf ("circle left\n");
  eSpeakSetGender ("female");
  eSpeakTalk ("circle left");
  rMotors (0.25, 0.75);

 /* line 4: "Can you tie them in a bow?" */  
  rBeep (0.25, pitchG5);
  rBeep (0.25, pitchA5);
  rBeep (0.20, pitchB5);
  rBeep (0.20, pitchA5);
  rBeep (0.20, pitchA5);
  rBeep (0.20, pitchGs5);
  rBeep (0.50, pitchA5);

  /* line 5: "Can you throw them o'er your shoulder" */
  rBeep (0.25, pitchB5);
  rBeep (0.25, pitchA5);
  rBeep (0.20, pitchG5);
  rBeep (0.20, pitchA5);
  rBeep (0.20, pitchG5);
  rBeep (0.20, pitchA5);
  rBeep (0.20, pitchG5);
  rBeep (0.20, pitchD5);
 

  /* line 6: "like a continental soldier?" */
  rBeep (0.20, pitchB4);
  rBeep (0.20, pitchC5);
  rBeep (0.20, pitchD5);
  rBeep (0.20, pitchE5);
  rBeep (0.20, pitchD5);
  rBeep (0.20, pitchB4);
  rBeep (0.20, pitchD5);
  rBeep (0.20, pitchD5);


  /* line 7: "Do your ears hang low?" */
  rBeep (0.20, pitchG5);
  rBeep (0.20, pitchA5);
  rBeep (0.7, pitchB5);
  rBeep (0.8, pitchA5);
  rBeep (1.1, pitchG5);

  rMotors (0.0, 0.0);

  /* Finish up with both the robot and eSpeak*/
  rDisconnect ();
  eSpeakDisconnect ();

  return 0;
}
