/* This program tests the full text-to-speech capability
 * of eSpeak in conjunction with the scribbler robot. 
 *
 * The scribbler will follow a series of commands dictated by
 * eSpeak. 
 * 
 * This test is based upon CSC161 - Project 4 by:
 * Jordan Yuan, Kyle Walters, Reed Caron
 * 
 * Author: Jordan Yuan
 * Date Created 10-2-2013
 * Date Revised 10-2-2013
 */

/* Compile this program with the line
 *  gcc -I/home/walker/Myro/include/MyroC -L/home/walker/Myro/lib -leSpeakPackage -lMyroC -ljpeg -lbluetooth -o eSpeakExample2 eSpeakExample2.c 
 *      or
 *  make eSpeakExample2 
 */

#include "eSpeakPackage.h"
#include <stdio.h>
#include <string.h>
#include "MyroC.h"
 

 /* List of  musical notes setting the sound frequencies that we want. */
  const int pitchC5  = 523;
  const int pitchD5  = 587;
  const int pitchE5  = 659;
  const int pitchF5  = 698;
  const int pitchG5  = 783;

/* testing sequence combining eSpeak commentary with
           testing of robot movement
*/
void MovementTest(){
  eSpeakTalk ("Move forward for 2");
  rForward(2.0,2.0);

  eSpeakTalk("Turn left");
  rTurnLeft(1.0,1.0);//turn left

  eSpeakTalk ("Move forward for 2");
  rForward(2.0,2.0);

  eSpeakTalk("Turn right");
  rTurnRight(1.0,1.0);//turn right

  eSpeakTalk ("Move forward for 2");
  rForward(2.0,2.0);

  eSpeakTalk("Turn left");
  rTurnLeft(1.0,1.0);//turn left

  eSpeakTalk("Turn right");
  rTurnRight(1.0,1.0);//turn right

  eSpeakTalk ("Move forward for 2");
  rForward(2.0,2.0);

}

/* testing sequence combining eSpeak commentary with
           testing of robot tone generation
*/
void SongTest(){
 
  eSpeakTalk("Ode to Joy by Ludwig van Beethoven ");
  //measure 1
  rBeep(.5, pitchE5);
  rBeep(.5, pitchE5);
  rBeep(.5, pitchF5);
  rBeep(.5, pitchG5);
  rBeep(.5, pitchG5);
  rBeep(.5, pitchF5);
  rBeep(.5, pitchE5);
  rBeep(.5, pitchD5);
  rBeep(.5, pitchC5);
  rBeep(.5, pitchC5);
  rBeep(.5, pitchD5);
  rBeep(.5, pitchE5);
  rBeep(.75, pitchE5);
  rBeep(.25, pitchD5);
  rBeep(1.0, pitchD5);

  //measure 2
  rBeep(.5, pitchE5);
  rBeep(.5, pitchE5);
  rBeep(.5, pitchF5);
  rBeep(.5, pitchG5);
  rBeep(.5, pitchG5);
  rBeep(.5, pitchF5);
  rBeep(.5, pitchE5);
  rBeep(.5, pitchD5);
  rBeep(.5, pitchC5);
  rBeep(.5, pitchC5);
  rBeep(.5, pitchD5);
  rBeep(.75, pitchE5);
  rBeep(.75, pitchD5);
  rBeep(.75, pitchC5);
  rBeep(1.20, pitchC5);
}//end of SongTest

/* testing sequence combining eSpeak commentary with
           testing of a combination of robot movement and tone generation
*/
void SongMoveTest(){
  eSpeakTalk("Beep Beep and move forward for 2 ");
  rBeep2(1.0,pitchD5,pitchE5);
  rForward(2.0,2.0);

  eSpeakTalk("Beep Beep and move backward for 2");
  rBeep2(1.0,pitchC5,pitchE5);
  rBackward(2.0,2.0);
}

int main ()
{
  /* set up eSpeak environment */
  eSpeakConnect (); //espeak has to connect first!

  /* set up scribbler environment */
  rConnect ("/dev/rfcomm0"); 
  eSpeakTalk("Connection established");

  //start of test
  eSpeakTalk ("the test begins");
  eSpeakSetGender ("female");//set gender female
  eSpeakTalk("Hello, welcome to the Grinnell Computer Science one sixty one");
  eSpeakTalk(" The test will begin.");
  MovementTest();//robot dance

  eSpeakTalk("Commence gender change in three, two one");
  eSpeakSetGender ("male");//set gender male 
  eSpeakTalk(" we will move to test number two");
  eSpeakTalk("test two");
  SongTest();

  eSpeakSetGender("female");//set gender female
  eSpeakTalk("We will now start test number three");
  SongMoveTest();

  /* finish up */
  eSpeakDisconnect ();//disconnect from eSpeak environment
  rDisconnect();//disconnect from scribbler environment

  printf("done");
  return 0;
}//end main
