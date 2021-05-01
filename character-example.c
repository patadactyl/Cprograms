/* program to illustrate the use of the char data type
 */

#include <stdio.h>
#include <ctype.h>  /* draw upon several useful char functions */

int main ()
{
  /* variable declarations */
  char ch1 = 'a';
  char ch2 = '?';
  char ch3 = '7';
  char ch4 = '\\';
  char ch5, ch6, ch7, ch8;

  /* character encoding is required to increase by 1
     for each digit 0, 1, 2, ..., 9
  */
  ch5 = ch3 + 1;   // char is a small int, so addition possible
  ch6 = ch5 - 4;   // subtraction also possible

  /* compare two characters by comparing encodings */
  if (ch6 == '4')
    printf ("ch6 is digit '4'\n");
  else
    printf ("ch6 is NOT digit '4'\n");

  /* utilize ctype library */
  /* determine if ch1 is a digit 0, ..., 9 */
  if (isdigit (ch1))
    printf ("%c is a digit\n", ch1);
  else
    printf ("%c is not a digit\n", ch1);

  /* convert lower case letter to upper case,
     other characters not changed */
  ch7 = toupper (ch1);
  ch8 = toupper (ch2);

  /* print characters and their codes */
  printf ("characters and their codes\n");
  printf ("character\tcode\n");
  printf ("   %c \t\t %d\n", ch1, ch1);
  printf ("   %c \t\t %d\n", ch2, ch2);
  printf ("   %c \t\t %d\n", ch3, ch3);
  printf ("   %c \t\t %d\n", ch4, ch4);
  printf ("   %c \t\t %d\n", ch5, ch5);
  printf ("   %c \t\t %d\n", ch6, ch6);
  printf ("   %c \t\t %d\n", ch7, ch7);
  printf ("   %c \t\t %d\n", ch8, ch8);

  
  return 0;
}
