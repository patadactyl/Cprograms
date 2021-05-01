/** This test demonstrate the basic text-to-speech capability of eSpeak
 *
 * Author: Jordan Yuan
 * Date created: 10-2-2013
 * Date revised: 10-9-2013
 */

/* Compile this program with the line
 *  gcc -Wall -Wno-deprecated-declarations -std=gnu99 -pthread -lMyroC -leSpeakPackage  -lMyroC -leSpeakPackage -framework OpenGL -framework GLUT   eSpeakExample1.c   -o eSpeakExample1
 *      or
 *  make eSpeakExample1
 */

#include "eSpeakPackage.h"

int main ()
{
  eSpeakConnect ();//connect to eSpeakSpeak
                   //voice set randomly to female or male
  eSpeakTalk( "setting up testing environment");

  eSpeakTalk( "setting voice to male");
  eSpeakSetGender ("male"); //set gender male

  eSpeakTalk("Once upon a time in a kingdom far far away");
  eSpeakSetGender("female"); // set gender female

  eSpeakTalk("there was a little princess");
  eSpeakTalk("who loves to stare into the stars");

  eSpeakSetGender("male");
  eSpeakTalk("one day a big dragon swooped down and they became the best of friends");

  eSpeakSetGender("female");
  eSpeakTalk("The end");

  eSpeakDisconnect ();//disconnect from eSpeak
} //end of main
