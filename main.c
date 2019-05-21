#include <stdio.h>
#include <malloc.h>
#include "functions.h"

int main() {
    char * userInput;
    int userInputLength;

    //Get valid user input
    do {
        printf("1. Read from console\n2. Read from file");
        userInput = getField(malloc(sizeof(char)), stdin, &userInputLength);
        if((userInputLength == 1) && ((int)userInput[0] == 49 || (int)userInput[0] == 50)){ break; }
    }while(1);
}