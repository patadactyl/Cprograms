/* A simple program to convert a number of quarts to liters
   Version with user input
*/

#include <stdio.h>

int main ()
{
    printf ("This program converts a number of quarts to liters\n");  

    int quarts; 
    double liters;

    printf ("Enter number of quarts (an integer):  ");
    scanf ("%d", &quarts);
    liters = quarts / 1.056710 ;

    printf ("%d quarts = %lf liters\n", quarts, liters);

    return 0;
}
