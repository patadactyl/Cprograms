//
//  testProblem4.c
//  
//
//  Created by Patrick Charlton on 4/13/19.
//

#include <stdio.h>

typedef struct node * movieList;

typedef struct node {
    Picture pic;
    movieList next;
}   movieNode;

void addPicture (movieList * first, Picture frame) {
    
    struct node * movieNode;
    
    movieNode->pic = frame;
    movieNode->next = NULL;
    
    if (*first == NULL) {
        first = movieNode;
    } else {
        while (movieNode->next != NULL) {
            first = movieNode->next;
        }
    }
}
