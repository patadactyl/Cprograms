/* This program illustrates how to 
      connect to the Scribbler robot, 
      beep, and 
      disconnect. 
 */

#include "MyroC.h" // include the library for Scribbler commands
#include "stdio.h"

int main()
{
    /* octave 5 */
    const int pitchC5  =  523;
    const int pitchDf5 =  554;
    const int pitchCs5 =  554;
    const int pitchD5  =  587;
    const int pitchEf5 =  622;
    const int pitchDs5 =  622;
    const int pitchE5  =  659;
    const int pitchF5  =  698;
    const int pitchGf5 =  739;
    const int pitchFs5 =  739;
    const int pitchG5  =  783;
    const int pitchAf5 =  830;
    const int pitchGs5 =  830;
    const int pitchA5  =  880;
    const int pitchBf5 =  932;
    const int pitchAs5 =  932;
    const int pitchB5  =  988;
    
    /* octave 6 */
    const int pitchC6  = 1047;
    const int pitchDf6 = 1109;
    const int pitchCs6 = 1109;
    const int pitchD6  = 1175;
    const int pitchEf6 = 1245;
    const int pitchDs6 = 1245;
    const int pitchE6  = 1319;
    const int pitchF6  = 1397;
    const int pitchGf6 = 1480;
    const int pitchFs6 = 1480;
    const int pitchG6  = 1568;
    const int pitchAf6 = 1661;
    const int pitchGs6 = 1661;
    const int pitchA6  = 1760;
    const int pitchBf6 = 1865;
    const int pitchAs6 = 1865;
    const int pitchB6  = 1976;
    
    int frequency;  // variable declaration to set frequency as an int for the beep
    double duration; // variable declaration to set the duration in seconds for the beep
    
    rConnect("/dev/rfcomm0"); // connect to Scribbler

    // printf("Insert a double value for the beep's duration in seconds and an int value for frequency...");
    
    scanf("%d", &frequency); // scan in integer value for frequency
    scanf("%lf", &duration); // scan in integer value for duration in seconds
    
    rBeep(duration, frequency); // allow user input for duration in seconds and frequency of beeps
    
    rBeep(1, pitchE5);
    rBeep(0.5, pitchE5);
    rBeep(0.5, pitchE5);
    rBeep(0.5, );
    rBeep(1, );
    rBeep(3, );
    rBeep(0.33, );
    rBeep(0.33, );
    rBeep(0.33, );
    
    rBeep(1, );
    rBeep(0.33, );
    rBeep(0.33, );
    rBeep(0.33, );
    rBeep(0.5, );
    rBeep(0.5, );
    rBeep(1, );
    rBeep(3, );
    
    rDisconnect(); // disconnect from Scribbler

    return 0; // return, indicating no errors have occurred
}   // main
