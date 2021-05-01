/* A simple program to convert a number of quarts to liters
   eSpeak added to announce steps of processing
*/

#include <stdio.h>                    /* reference to standard I/O library */
#include "eSpeakPackage.h"

int main ()                           /* beginning of main program */
  {  
    /* declarations */
    int quarts; 
    double liters;

    eSpeakConnect();                  /* set up eSpeak speech synthesizer */
      
  void SongTest(){

    printf ("This program converts a number of quarts to liters\n");  
    eSpeakTalk ("starting program\n");  /* convert string to spoken text */

    eSpeakSetGender("female");        /* set gender female */
    eSpeakTalk ("Computing values");  /* annouce this code segment */
    quarts = 2;                       
    liters = quarts / 1.056710 ;      

    eSpeakTalk ("printing        ");  /* announce next code segment */
    printf ("%d quarts = %lf liters\n", quarts, liters);

    eSpeakSetGender("male");
      eSpeakTalk ("program done but I am sad I am only a computer no one can love a computer.");      /* last announcement */
    eSpeakDisconnect ();              /* work with eSpeak completed */

    return 0;                        
  }
