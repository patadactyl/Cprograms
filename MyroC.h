/**
 *  @file MyroC.h                                                          
 *  @brief Header for a C-based, my-robot package for the Scribbler 2      
 *                                                                          
 * Revision History
 *
 * Version 1.0 based on a C++ package by April O'Neill, David Cowden,
 *     Dilan Ustek, Erik Opavsky, and Henry M. Walker
 *
 * Developers of the C package for Linux:
 *  Creators Version 2.0 (C functions for utilities,general,sensors,movement):
 *    Spencer Liberto
 *    Dilan Ustek
 *    Jordan Yuan
 *    Henry M. Walker
 *  Contributors Version 2.2-2.3: (C functions for image processing)
 *    Anita DeWitt
 *    Jason Liu
 *    Nick Knoebber
 *    Vasilisa Bashlovkina
 * Revision for Version 2.4:  (image row/column made to match matrix notation)
 *    Henry M. Walker
 *
 * Revisions for Version 3.0 
 *    Henry M. Walker
 *
 *  C ported to Macintosh
 *     Linux/Mac differences required for connections — otherwise same code
 *  OpenGL used to display images, replacing ImageMagick
 *     same [new] code used for both Linux and Macintosh
 *     1 process for robot control
 *     1 process needed for each titled window (not each image, as in 2.2-2.4)
 *  Blocking options (negative duration parameter)
 *     utilize separate thread timer
 *  MyroC implementation files organized by user function as follows:
 *
 * Revisions for Version 3.1 
 *    Henry M. Walker
 *
 *    Picture struct and image functions revised to allow 
 *       192 by  256 images from origial Fluke camera
 *       266 x 427 low-resolution images from Fluke 2
 *         (high-resolution (800 x 1280) too large for more than 2-4 
 *          variables on run-time stack)
 *       storage, retrieval, and display of any images up to 266 x 427 
 *
 * Revisions for Version 3.2
 *    Henry M. Walker
 *    
 *    Practical range of rBeep duration identified as <= 3.0014 seconds
 *    Image display and processing resolves several matters and adds functionality
 *        function rDisplayPicture completely rewritten
 *                over time OpenGL rountines had encountered troubles
 *                on Linux, specifically glutHideWindow() hid images, but could not be
 *                          restored, with difficulties depending on the graphics card
 *                on Mac, High Sierra generated compile warnings and 
 *                          restricted threads that could display images
 *    function rDisplayImageProcessingErrors added
 *    function rWaitTimedImageDisplay updated substantially
 *
 *  This program and all MyroC software is licensed under the Creative Commons
 *  Attribution-Noncommercial-Share Alike 3.0 United States License.
 *  Details may be found at http://creativecommons.org/licenses/by-nc-sa/3.0/us/
 *
 *  
 ************************************************************************
 */


/*
 ********************** implementation overview *************************
 *  MyroC implementation files organized by user function as follows:

 1. GENERAL                          2. SENSORS
    rConnect                          a.Scribbler Sensors
    rDisconnect                         rGetLightsAll
    rSetConnection                      rGetLightTxt
    rFinishProcessing                   rGetIRAll
    rSetVolume                          rGetIRTxt
    rBeep                               rGetLine
    rBeep2                        
    rSetName                          b.Fluke Sensors
    rGetName                            rGetObstacleAll
    rSetForwardness                     rGetObstacleTxt
    rGetForwardness                     rGetBrightAll
    rSetLEDFront                        rGetBrightTxt
    rSetLEDBack                         rSetIRPower
    rGetBattery    
    rGetStall

3.  MOVEMENT                         4.  PICTURES
    rTurnLeft                            rGetCameraSize
    rTurnRight                           rTakePicture
    rTurnSpeed                           rDisplayPicture
    rForward                             rDisplayImageProcessingErrors
    rFastForward                         rWaitTimedImageDisplay
    rBackward                            rSavePicture
    rMotors                              rLoadPicture
    rStop
    rHardStop   
*/

#ifndef _MyroC
#define _MyroC
/**
 * @brief Struct for a pixel
 */
typedef struct
{
  unsigned char R; //!< The value of the red component 
  unsigned char G; //!< The value of the green component 
  unsigned char B; //!< The value of the blue component 
} Pixel;

/**
 * @brief Struct for a picture object
 * @note images from robot cameras have varying sizes, depending on the Fluke
 * @note pix_array is sufficiently large to accommodate any Fluke version
 * @note    images for the original Fluke are 192 (height) by 256 (width)
 * @note    low-resolution images for the Fluke 2 are 266 by 427
 * @note    high-resolution images (e.g., 800 by 1280) are not practical,
 *             due to memory constraints and thus are not available in MyroC
 * @note    user-defined images may have any size, as long as
 *          height <= 266 and width <= 427
 * @note Following standard mathematical convention for a 2D matrix, 
 *       all references to a pixel are given within an array as [row][col]
 *
 * @warning The Picture struct is defined to be sufficiently large
 *          to store several low-resolution camera images (340756 bytes each)
 *             Experimentally, an array of up to 94 (not 95) Pictures is allowed
 *             However, the display of images requires that image data
 *                be copied, so display of many images may not work
 *          If a program hangs when working with Picture variables,
 *             the issue may involve lack of space on the runtime stack.
 *             To utilize a modest number of Pictures,   
 *             use "ulimit -s"  command, as needed, in a terminal window
 *             For example, ulimit -s 32768
 *             Sizes above 32768 may not be allowed in Linux or Mac OS X
 */
typedef struct 
{
  int height; //!< The actual height of the image, but no more than 266
  int width;  //!< The actual width of the image, but no more than 427
  Pixel pix_array[266][427]; //!< The array of pixels comprising the image
} Picture;

/* ***************************************************************/
/* 1. GENERAL - GENERAL - GENERAL - GENERAL - GENERAL - GENERAL  */
/* ***************************************************************/

/**
 * @brief connects program to Scribbler
 * @param address  string, giving name of workstation port
 *                 or a Scribbler Bluetooth designation
 *
 *                 several string formats are possible                      \n
 *                 Linux and Mac:                                           \n
 *                   a communications port, such as "/dev/rfcomm0"          \n
 *                   a Scribbler 2 fluke serial number, such as "245787"    \n
 *                   a full IPRE serial number, such as "IPRE245787"        \n
 *                   a Fluke 2 serial number (hexadecimal), such as "021F"  \n
 *                   a full Fluke 2 serial number, such as "Fluke2-021F"    \n
 *                 Linux only:                                              \n
 *                   a MAC address, such as "00:1E:19:01:0E:13"             \n
 *                 Mac only:                                                \n
 *                    any substring of a complete device file name,         \n
 *                       as long as the resulting device is unique          \n
 *                    some possibilities include                            \n
 *                       a complete device file name, such as               \n
 *                         + "/dev/tty.IPRE6-365877-DevB"                   \n
 *                         + "/dev/tty.Fluke2-0958-Fluke2"                  \n
 *                       a fluke or fluke2 serial number                    \n
 *                       full path of symbolic link to a device filename string
 *                         or substring in /dev 
 *
 *                    uniqueness is ensured by requiring 4 hex digits       \n 
 *                       or 6 decimal digits
 *                   
 * @return         the socket number of communications port
 *
 * @post           subsequent communications will take place through
 *                 this socket, unless changed by rSetConnection
 */
int rConnect (const char * address);

/**
 * @brief stop Scribbler motion and close Bluetooth
 *
 * @post                  motion for the current robot is stopped,
 *                           blocking until any non-blocking motion time
 *                           has expired                                      \n
 *                           i.e., if a motion timer is set,                  \n
 *                                    this procedure blocks                   \n
 *                                    when the timer completes,               \n
 *                                         then the motion stops              \n
 *                                 else, procedure stops motion immediately   \n
 *                        Bluetooth for the current robot is closed
 */
void rDisconnect();

/**
 * @brief set current connection to the socket number
 * @param new_socket_num  the number of an open socket for communication
 * @pre                   new_socket_num has been returned by rConnect
 *                        the designated socket has not been closed
 */
void rSetConnection (int new_socket_num);

/**
 * @brief                 all timed motions/image displays completed, 
 *                        all robots stopped, and 
 *                        all robot Bluetooth connections closed
 *
 * @brief                 same result as  rDisconnect for all robots
 *                        plus  rComleteImageDisplay
 *
 * @post                  blocks until all timed robot motions are complete,
 *                           and all timed image displays no longer visible  \n
 *                        upon completion, all timed images are invisible,
 *                           all robot motion is halted, and
 *                           all robot Bluetooth connections closed
 */
void rFinishProcessing ();

/**
 * @brief Set sound to high volume (H) or mute (M)
 * @parm highMute   set volume of Scribbler
 * @pre             highMute is 'H' to set for high volume
 *                  or 'M' for mute
 */
void rSetVolume (char highMute);

/**
 * @brief Beeps with the given duration and frequency
 * @param duration   length of note in seconds
 * @param frequency  frequency of pitch in cycles per second (hertz)
 * @pre              0.0 < duration > 0.0 <= 3.0 seconds
 *                   (Scribbler 2 hangs if duration > 3.0014 seconds;
 *                    although reason unknown,
 *                    experimentation suggests part of Sribbler 2 firmware)
 */
void rBeep(double duration, int frequency);

/**
 * @brief Generates two notes for the prescribed duration
 * @param duration  length of note in seconds
 * @param freq1     frequency of first pitch in cycles per second (hertz)
 * @param freq2     frequency of second pitch in cycles per second (hertz)
 * @pre             0.0 < duration <= 3.0 seconds
 *                  (Scribbler 2 hangs if duration > 3.0014 seconds;
 *                   although reason unknown,
 *                   experimentation suggests part of Sribbler 2 firmware)
 */
void rBeep2(double duration, int freq1, int freq2);

/**
 * @brief Change name stored in the robot to the 16-byte name given
 * @param name  specifies new name of robot                                   \n
 *              if < 16 bytes given, name is filled with null characters      \n
 *              if >= 16 bytes given, name is truncated to 15 bytes plus null \n
 */
void rSetName (const char * name);

/**
 * @brief Get the name of the robot
 * @return information about the name of the robot
 * @post  the returned name is a newly-allocated 17-byte string
 */
const char * rGetName();

/**
 * @brief specifies which end of the Scribbler is considered the front
 * @param direction  identifies front direction
 * @pre              direction is either "fluke-forward" or "scribbler-forward"
 *                   (not case sensitive)
*/
void rSetForwardness(char * direction);

/**
 * @brief alternative to rSetForwardness for compatibility with earlier MyroC 
 */
void rSetForwardnessTxt (char * direction);

/**
 * @brief Gets the forwardness of the Scribbler
 * @return either "fluke-forward" or "scribbler-forward"
 */
char * rGetForwardness ();

/**
 * @brief Set the front [fluke] LED on or off
 * @param led  value 1 turns on LED
 *             value 0 turns off LED
 * @pre        led must be 0 or 1
 */
void rSetLEDFront(int led);

/**
 * @brief Set the the intensity of the back fluke LED
 * @param led  intensity of the LED                                         \n
 *             values between 0 and 1 provide a range of brightness
 *               from off to full intensity                                 \n
 *             values bigger than 1 are treated as 1 (full brightness)      \n
 *             values less than 0 are treated as 0 (LED off)
 */
void rSetLEDBack(double led);

/**
 * @brief Get the current voltage from the Scribbler batteries;
 *        Maximum charge from 6 batteries could be up to 6 volts;
 *        Manufacturer suggests batteries should be changed below 4.1 volts
 * @return  percentage of battery voltage
 */
double rGetBattery();

/** 
 * Determine if robot has stalled
 *
 * MyroC Reference Manual 
 *     (http://wiki.roboteducation.org/Myro_Reference_Manual) states
 *   "Every time you issue a move command, the stall sensor resets, and it 
 *   needs to wait a short time to see whether the motors are stalled.  
 *   This means that the sensor won't give accurate results if you test 
 *   it too soon after the robot starts to move."
 *
 * In practice, it may take 0.5-1.0 seconds for rGetStall to sense
 *    the robot is stalled
 *
 * @param sampleSize  how many readings are taken for each sensor
 * @pre               sampleSize > 0
 * @return            whether or not robot current has stalled
 * @post              Returns 1 if the robot has stalled                  \n
 *                    Returns 0 otherwise.
 */
int rGetStall (int sampleSize);

/**
 * @brief Turn on and off echoing of Bluetooth transmissions
 * All robot commands involve the transmission of a command over Bluetooth
 *   Scribbler commands are always 9 bytes                                \n
 *   Fluke commands have varying lengths                                  \n
 * The fluke echos most, but not all, of the commands                     \n
 * For many commands, the fluke also echos 11 bytes of sensor data
 * @param onOff      char 'y' enables echoing                             \n
 *                   char 'n' disables echoing                            \n
 *                   other character values ignored
 */
void rSetBluetoothEcho (char onOff);


/* ************************************************************************/
/* 2. SENSORS - SENSORS - SENSORS - SENSORS - SENSORS - SENSORS - SENSORS */
/* ************************************************************************/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*  Group a:  Scribbler Sensors                                          */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * @brief Get the average values of each of the three light sensors in an array.
 * Values of each light sensor can somewhat (typically under 5%-10%).
 * To even out variability, the sensor can be queried sampleSize times
 * and an average obtained.
 * @param lightSensors  array to store intensity values
 * @param sampleSize   how many readings are taken for each sensor
 * @pre                space already allocated for lightSensors array
 *                     sampleSize > 0
 * @post  
 *                     lightSensors[0] gives average value for left sensor   \n
 *                     lightSensors[1] gives average value for middle sensor \n
 *                     lightSensors[2] gives average value for right sensor  \n
 *                     Intensity values near 0 represent bright light        \n
 *                     Intensities may extend to about 65000 for a dark region.
*/
void rGetLightsAll (int lightSensors[3], int sampleSize);

/**
 * @brief Get the average values of a specified light sensor.
 * Values of each light sensor can somewhat (typically under 5%-10%).
 * To even out variability, the sensor can be queried sampleSize times
 * and an average obtained.
 * @param sensorName   name of the light sensor
 * @pre                sensorName is "left", "center", "middle", or "right"
 *                     (not case sensitive)                                 \n
 *                     designations "center" and "middle" are alternatives
 *                     for the same light sensor
 * @param sampleSize   how many readings are taken for the sensor
 * @pre                sampleSize > 0
 * @return             reading from the specified light sensor, averaged
 *                     over sampleSize number of data samples               \n
 *                     if sensorName invalid, returns -1.0
 */
int rGetLightTxt (const char * sensorName, int sampleSize);

/**
 * @brief Get an array of true/false values regarding the presence of obstacle
 * based on the average values of each of the three IR sensors.
 * Since readings of each light sensor can vary substantially,
 *    each sensor can be queried sampleSize times and an average obtained.
 * @param irSensors   array to store intensity values
 * @param sampleSize  how many readings are taken for each sensor
 * @pre               space already allocated for irSensors array
 *                    sampleSize > 0
 * @post  
 *                    irSensors[0] checks obstacle for left sensor         \n
 *                    irSensors[1] checks obstacle for right sensor
 * @post              for each irSensors array value                       \n
 *                    return 0 indicates no obstacle detected              \n
 *                    return 1 indicates obstacle detected  
*/
void rGetIRAll (int irSensors[2], int sampleSize);


/**
 * @brief Use specified IR sensor to determine if obstacle is present.
 * Since values of each light sensor can vary substantially,
 * the sensor can be queried sampleSize times and an average obtained.
 * @param sensorName   name of the light sensor
 * @pre                sensorName is "left" or "right"
 *                     (not case sensitive)
 * @param sampleSize   how many readings are taken for the sensor
 * @pre                sampleSize > 0
 * @return             true/false (0/1) determination of obstacle, based on IR
 *                     sensorName sensor, averaged over sampleSize number of
 *                     data samples
 * @post               return 0 indicates no obstacle detected            \n
 *                     return 1 indicates obstacle detected
*/
int rGetIRTxt (const char * sensorName, int sampleSize);

/**
 * @brief Use Scribbler 2 line sensors of Scribbler to check for a black line
 * on a white surface under the robot.
 * Since values of each light sensor can vary substantially,
 *    the sensor can be queried sampleSize times and an average obtained.
 * @warning            results of these sensors may be flakey!
 * @param lineSensors  array to store line values detected
 * @param sampleSize   how many readings are taken for each sensor
 * @pre                space already allocated for lineSensors array
 *                     sampleSize > 0
 * @post               lineSensors[0] checks left sensor for line        \n
 *                     lineSensors[1] checks right sensor for line
 * @post               for each irSensors array value                    \n
 *                     return 0 indicates line is identified             \n
 *                     return 1 indicates line is not identified
 */
void rGetLine (int lineSensors[2], int sampleSize);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*  Group b:  Fluke Sensors                                              */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * @brief Set the amount of power for the dongle's IR sensors
 * @param power  the desired power level for the IR sensors
 * @pre          power is between 0 and 255 (inclusive)                  \n
 *               Manufacturer notes:  default value is 135               \n
 *                   if IR obstacle sensor is always high, try lowering IR power \n
 *                   if IR obstacle sensor is always low,  try raising IR power  \n
 */
void rSetIRPower (int power);

/**
 * @brief Get the average values of the three obstacle sensors in an array.
 * Since readings of each obstacle sensor can vary substantially (successive
 *      readings may differ by several hundred or more),
 *      each sensor can be queried sampleSize times and an average obtained.
 * @param obstSensors   array to store intensity values
 * @param sampleSize    how many readings are taken for each sensor
 * @pre                 space already allocated for obstSensors array;
 *                      sampleSize > 0
 * @post                obstSensors[0] gives average value for left sensor    \n
 *                      obstSensors[1] gives average value for middle sensor  \n
 *                      obstSensors[2] gives average value for right sensor   \n
 *                      Returned values are between 0 and 6400                \n
 *                      Obstacle values near 0 represent no obstacle seen     \n
 *                      Obstacle values may approach 6400 as obstacle gets close.
 * @warning             As battery degrades, sensor readings degrade,
 *                      yielding systematically lower numbers.
 */
void rGetObstacleAll (int obstSensors[3], int sampleSize);

/** 
 * @brief Get the average values of a specified obstacle (IR) sensor.
 * Since values of each obstacle sensor can vary substantially (successive
 *      readings may differ by several hundred or more),
 *      the sensor can be queried sampleSize times and an average obtained.
 * @param sensorName  name of the obstacle sensor
 * @pre               sensorName is "left", "center", "middle", or "right"
 *                    (not case sensitive)                                   \n
 *                    designations "center" and "middle" are alternatives
 *                    for the same light sensor
 * @param sampleSize  how many readings are taken for the sensor
 * @pre               space already allocated for vals array;
 *                    sampleSize > 0
 * @return            reading from the specified obstacle sensor, averaged
 *                       over sampleSize number of data samples              \n
 *                    Returned values are between 0 and 6400                 \n
 *                    Obstacle values near 0 represent no obstacle seen      \n
 *                    Obstacle values may approach 6400 as obstacle gets close.
 * @warning           As battery degrades, sensor values degrade,
 *                    yielding systematically lower numbers.
 */
int rGetObstacleTxt (const char * sensorName, int sampleSize);

/**
 * @brief Read the Fluke's virtual light sensors.
 *  Since readings of each brightness sensor can vary substantially (successive
 *     readings may differ by 5000-10000),
 *     each sensor can be queried sampleSize times and an average obtained.
 * @param brightSensors  array to store intensity values
 * @param sampleSize     how many readings are taken for each sensor
 * @pre                  space already allocated for brightSensors array
 *                       sampleSize > 0
 * @post                 brightSensors[0] gives average value for left sensor   \n
 *                       brightSensors[1] gives average value for middle sensor \n
 *                       brightSensors[2] gives average value for right sensor  \n
 *                       Brightness values near 0 represent bright light        \n
 *                       Brightness values may extend to about 65535 for a dark region.
 */
void rGetBrightAll (int brightSensors[3], int sampleSize);

/**
 * @brief Reads one of the Fluke's virtual light sensors.
 * Each sensor reports a total intensity in the left, middle, or right of the
 *    Fluke's camera
 * Since values of each obstacle sensor can vary substantially (successive
 *    readings may differ by 5000-10000),
 *    the sensor can be queried sampleSize times and an average obtained.
 * @param sensorName  name of the bright sensor
 * @pre               sensorName is "left", "center", "middle", or "right"
 *                    (not case sensitive)                                     \n
 *                    designations "center" and "middle" are alternatives
 *                    for the same bright sensor
 * @param sampleSize  how many readings are taken for the sensor
 * @pre               sampleSize > 0
 * @return            reading from the specified bright sensor, averaged
 *                    over sampleSize number of data samples                  \n
 *                    Brightness values near 0 represent bright light         \n
 *                    Brightness values may extend to about 65535 for a very dark region.
 */
int rGetBrightTxt (char * sensorName, int sampleSize);

/**
 * @brief returns information about the robot's dongle, firmware, and 
 * communication mode as a 60 character array in infoBuffer. 
 * @param infoBuffer  a pre-defined, 60-character array 
 * @post              infoBuffer contains relevant robot information
 */
void rGetInfo (char * infoBuffer);


/* *********************************************************************/
/* 3. MOVEMENT - MOVEMENT - MOVEMENT - MOVEMENT - MOVEMENT - MOVEMENT  */
/* *********************************************************************/

/* Procedures in this section, except rMotors, include a "time" parameter.
 *
 * Throughout, "time" is interpreted as follows:
 *     if time > 0, the call to the procedure is "blocking:
 *            That is, a call to the procedure starts a motion, and
 *            all other processing stops for the specified time (in seconds).
 *            After the specified time interval, the motion stops,
 *            and processing in the main program continues.             \n
 *     If time == 0, the procedure is "non-blocking":
 *            That is, the procedure starts a motion, 
 *            and that motion continues until another motion command is issued.
 *            Once the motion starts, other processing in the main
 *            program continues.                                        \n
 *     If time < 0, the procedure is "non-blocking": 
 *            That is, a call to the procedure starts a motion,
 *            and a timer is started for the abs("time").               \n
 *            Once the time interval is completed,                      \n
 *               if no other motion command has been issued,
 *                  a command to stop robot motion is given             \n
 *               if another motion command has been issued (before the
 *                  specified time), the new command is executed immediately,
 *                  and the timer is ignored.                           \n
 *           For example, suppose rForward is called with a time of -5 seconds:
 *               subsequent processing in the main program continues    \n
 *               if numerous beeps are issued or the camera is used or
 *                  a series of non-motion commands are issued, then
 *                  the rForward action stops in 5 seconds.             \n
 *               if an rRightTurn command is issued after 2 seconds,
 *                  then the rForward command is overridden by rRightTurn
 *                  and the timer for rForward (after another 3 seconds)
 *                  is ignored.
 *
 * Program termination with timed, non-blocking commands:
 *    When a non-blocking time is specified (i.e., time < 0), processing within 
 *    the controlling program continues.  However, the robot's Bluetooth connection
 *    (established with rConnect) is not severed until the non-blocking timer has
 *    expired and the motion stopped.  In particular, rDisconnect blocks until
 *    the specified non-blocking time is completed and the program tells the
 *    robot to stop.
 */

/**
 * @brief turn Scribbler left for a specified time and speed
 * @param speed  the rate at which the robot should move left
 *               linear range:  -1.0 specifies right turn at full speed     \n
 *                              0.0 specifies no turn                       \n
 *                              1.0 specifies left turn at full speed       \n
 * @param time   specifies the duration of the turn                         \n
 *               if negative:    the robot starts to turn (non-blocking)
 *                               other processing proceeds, and
 *                               the robot continues to turn until given another
 *                               motion command or disconnected (non-blocking) \n
 *               if zero:        robot starts turning (non-blocking);
 *                               other processing proceeds                  \n
 *              if positive:     robot turns for the given duration, in seconds
 */
void rTurnLeft (double speed, double time);

/**
 * @brief turn Scribbler right for a specified time and speed  
 *  @param speed  the rate at which the robot should move right             \n
 *                linear range: -1.0 specifies left turn at full speed      \n
 *                              0.0 specifies no turn                       \n
 *                              1.0 specifies right turn at full speed
 * @param time   specifies the duration of the turn                         \n
 *               if negative:    the robot starts to turn (non-blocking)
 *                               other processing proceeds, and
 *                               the robot continues to turn until given another
 *                               motion command or disconnected (non-blocking) \n
 *               if zero:        robot starts turning (non-blocking);
 *                               other processing proceeds                     \n
 *              if positive:     robot turns for the given duration, in seconds \n
 *              if nonnegative:  robot turns for the given duration, in seconds
 */
void rTurnRight (double speed, double time);

/** 
 * @brief turn Scribbler in direction for a specified time and speed
 * @param direction  direction of turn, based on looking from
 *                   the center of the robot and facing forward
 * @param speed      the rate at which the robot should move forward        \n
 *                   linear range:  -1.0 specifies turn at full speed       \n
 *                                  0.0 specifies no turn                   \n
 *                                  1.0 specifies turn at full speed
 * @param time   specifies the duration of the turn                         \n
 *               if negative:    the robot starts to turn (non-blocking)
 *                               other processing proceeds, and
 *                               the robot continues to turn until given another
 *                               motion command or disconnected (non-blocking) \n
 *               if zero:        robot starts turning (non-blocking);
 *                               other processing proceeds                  \n
 *              if positive:     robot turns for the given duration, in seconds
 * @pre              direction is "left" or "right", case insensitive
 */
void rTurnSpeed (char * direction, double speed, double time);

/**
 * @brief moves Scribbler forward for a specified time and speed
 * @param speed   the rate at which the robot should move forward           \n
 *                linear range:  -1.0 specifies move backward at full speed \n
 *                               0.0 specifies no forward/backward movement \n
 *                               1.0 specifies move forward at full speed
 * @param time   specifies the duration of the turn                         \n
 *               if negative:    the robot starts forward (non-blocking)
 *                               other processing proceeds, and
 *                               the robot continues forward until given another
 *                               motion command or disconnected (non-blocking) \n
 *               if zero:        robot starts moving forward (non-blocking);
 *                               other processing proceeds                  \n
 *              if positive:     robot moves forward for the given duration, in seconds
 */
void rForward (double speed, double time);

/** 
 * @brief moves Scribbler forward at the largest possible speed for a specified time 
 * @param time   specifies the duration of the turn                        \n
 *               if negative:    the robot starts forward (non-blocking)
 *                               other processing proceeds, and
 *                               the robot continues forward until given another
 *                               motion command or disconnected (non-blocking) \n
 *               if zero:        robot starts moving forward (non-blocking);
 *                               other processing proceeds                 \n
 *              if positive:     robot moves forward for the given duration, in seconds
 * @warning     may take longer than usual to execute
 */
void rFastForward (double time);
 
/**
 * @brief moves Scribbler backward for a specified time and speed  
 * @param speed  the rate at which the robot should move backward          \n
 *               linear range:  -1.0 specifies move forward at full speed  \n
 *                              0.0 specifies no forward/backward movement \n
 *                              1.0 specifies move backward at full speed
 * @param time   specifies the duration of the turn                        \n
 *               if negative:    the robot starts backward (non-blocking)
 *                               other processing proceeds, and
 *                               the robot continues backward until given another
 *                               motion command or disconnected (non-blocking) \n
 *               if zero:        robot starts moving backward (non-blocking)
 *                               other processing proceeds                 \n
 *              if positive:     robot moves backward for the given duration, in seconds
 */
void rBackward (double speed, double time);

/**
 * @brief move robot with given speeds for the left and right motors
 * continues until given another motion command or disconnected (non-blocking)
 * @param leftSpeed  the rate at which the left wheel should turn          \n
 *              linear range:  -1.0 specifies move backward at full speed  \n
 *                              0.0 specifies no forward/backward movement \n
 *                              1.0 specifies move forwardward at full speed
 * @param rightSpeed the rate at which the right wheel should turn         \n
 *              linear range:  -1.0 specifies move backward at full speed  \n
 *                              0.0 specifies no forward/backward movement \n
 *                              1.0 specifies move forward at full speed
 */
void rMotors (double leftSpeed, double rightSpeed);

/**
 * @brief directs robot to stop movement
 */
void rStop();

/**
 * @brief cuts power to the motor of the robot
 */
void rHardStop();

/* *********************************************************************/
/* 4. PICTURES PICTURES PICTURES PICTURES PICTURES PICTURES PICTURES   */
/* *********************************************************************/
/**
 * This section contains functions for taking and manipulating images
 * All images are constrained with height <= 266 and width <= 427
 *
 * images from robot cameras have varying sizes, depending on the Fluke
 *     images for the original Fluke are 192 (height) by 256 (width)
 *     low-resolution images for the Fluke 2 are 266 by 427
 *     high-resolution images for the fluke 2 are 800 by 1280
 *
 * Bluetooth communication constrains the time required for the Fluke
 *        to take a picture
 *     Typical times:   original fluke:      2- 4 seconds
 *                      Fluke 2 (low res):   4- 6 seconds
 *                      Fluke 2 (high res): 25-30 seconds
 *
 *     BASED ON TIMINGS AND MEMORY CONSIDERATIONS, Myro C ALLOWS
 *     ONLY LOW RESOLUTION IMAGES
 *
 * the Picture struct allows direct access to Pixel data
 * Pictures can be saved and loaded as .jpeg files
 *
 * @note Following standard mathematical convention for a 2D matrix, 
 *       all references to a pixel are given within an array as [row][col]
 * @note    user-defined images may have any size, as long as
 *          height <= 266 and width <= 427
 * @note Following standard mathematical convention for a 2D matrix, 
 *       all references to a pixel are given within an array as [row][col]
 *
 * @warning The Picture struct is defined to be sufficiently large
 *          to store several low-resolution camera images (340756 bytes each)
 *             Experimentally, an array of up to 94 (not 95) Pictures is allowed
 *             However, the display of images requires that image data
 *                be copied, so display of many images may not work
 *          If a program hangs when working with Picture variables,
 *             the issue may involve lack of space on the runtime stack.
 *             To utilize a modest number of Pictures,   
 *             use "ulimit -s"  command, as needed, in a terminal window
 *             For example, ulimit -s 32768
 *             Sizes above 32768 may not be allowed in Linux or Mac OS X
 */

/**
 * @brief Use the camera to take a photo
 * @return Picture
 */
Picture rTakePicture();

/**
 * @brief Save a Picture to a .jpeg
 * @param pic      pointer to an RGB picture struct from Scribbler 2 camera
 * @param filename the name of the file
 * @pre            filename ends with .jpeg or .jpg.
 * @post           If the file does not exist, a new file will be created.
 * @post           If the file exists, the file will be overwritten.
 */
void rSavePicture(Picture * pic, char * filename);

/**
 * @brief Load a picture from a .jpeg file.
 * @param filename  the name of the file
 * @pre             file must exist
 * @pre             file must be a 256x192 .jpeg or .jpg
 * @return          Picture
 */
Picture rLoadPicture(char * filename);


/**
 * @brief Display a picture in a new window
 * @param pic         pointer to an RGB picture struct from Scribbler 2 camera
 * @param duration    if duration > 0, operation is blocking                 \n
 *                    if duration <= 0, operation is non-blocking            \n
 *                    for duration != 0, picture displayed for abs(duration) \n
 *                            seconds or until picture closed manually or 
 *                            until the program terminates                   \n
 *                    if duration == 0, picture displayed until closed manually
 * @param windowTitle The title of the window that appears.
 *                    white spaces will be replaced with underscores. 
 * @pre               windowTitle is less than 100 characters. 
 * @post              image is displayed for the duration specified,         \n
 *                    EXCEPT all display windows are closed 
 *                           when the main program terminates.
 * @warning           If images are displayed with a non-blocking option, and
 *                    if the user wants images to appear for a full duration,
 *                    use rWaitTimedImageDisplay or rFinishProcessing to block
 *                    processing until all image timers are finished.
 *                    Otherwise, program termination may close windows prematurely.
 */
void rDisplayPicture(Picture * pic, double duration, const char * windowTitle);

/** @brief Turn on and off the printing of error messasge for image processing
 *  @note  Some operating systems (e.g., Mac OX S High Sierra) display 
 *         an error message whenevern a new process for image display starts
 *  @post  This function toggles this printing on and off
 *         Initially, printing is off
 */
void rDisplayImageProcessingErrors ();

/**
 * @brief Wait until all timed, non-blocking image window timers are complete
 * @post              wait until all timed [non-blocking] images have closed \n
 *                    robot motion is unaffected by this function
 *
 * @warning           images opened with duration 0.0 do not close until 
 *                       images are updated or until the program terminates  \n
 *                    all other [timed, non-blocking] image windows 
 *                       are closed by this function
 */
void rWaitTimedImageDisplay ();

#endif
