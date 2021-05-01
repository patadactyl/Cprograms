//
//  Test - Problem 2.c
//  
//
//  Created by Patrick Charlton on 4/13/19.
//

#include <stdio.h>

void prA (int *r, int *s) {
    printf("prA 1 : r = %u; *s = %u\n", r, *s);
    *r = 17;
    *s = 13;
    printf("prA 2 : r = %u; *s = %u\n", r, *s);
}

void prB (int a, int *b) {
    printf("prB 1 : a = %u; *b = %u\n", a, *b);
    prA(&a, b);
    printf("prB 2 : a = %u; *b = %u\n", a, *b);
}

int main (void) {
    int x = 25;
    int y = 29;
    printf ("main 1: x = %u; y = %u\n", x, y);
    prB (x, &y);
    printf("main 2: x = %u; y = %u\n", x, y);
    return 0;
}
