#include <stdio.h>
#include <malloc.h>
#include "utilities.h"

int main() {
    char * userInput;
    int userInputLength;
    int firstRun = 1;

    //Get valid user input
    do {
        printf("1. Read from console\n2. Read from file\n");
        userInput = getField(malloc(sizeof(char)), stdin, &userInputLength);
        if((userInputLength == 1) && ((int)userInput[0] == 49 || (int)userInput[0] == 50)){
            if(firstRun){
                clearLines(3);
            }
            else{
                clearLines(4);
            }
            break;
        }
        else{
            //This re-prompts the user for input if what they entered is invalid, without spamming the console
            if(firstRun){
                clearLines(3);
                printf("Invalid input.\n");
                firstRun = 0;
            }
            else{
                clearLines(4);
                printf("Invalid input.\n");
            }
        }
    }while(1);
}