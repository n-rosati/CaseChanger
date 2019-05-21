#include <stdio.h>
#include <malloc.h>
#include "utilities.h"

int main(){
    char * userInput;
    int menuOption;
    int userInputLength;
    int firstRun = 1;
    int nonAlphaCounter = 0;

    //Get user input
    do {
        printf("1. Read from console\n2. Read from file\n");
        userInput = getField(malloc(sizeof(char)), stdin, &userInputLength);
        if((userInputLength == 1) && ((int)userInput[0] == 49 || (int)userInput[0] == 50)){
            if(firstRun){ clearLines(3); }
            else{ clearLines(4); }
            menuOption = (int)userInput[0] - 48;
            free(userInput);
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
        free(userInput);
    }while(1);

    switch (menuOption){
        case 1:
            userInput = getField(malloc(sizeof(char)), stdin, &userInputLength);
            for (int i = 0; i < userInputLength; ++i) {
                if(!(((userInput[i] >= 65) && (userInput[i] <=90)) || ((userInput[i] >= 97) && (userInput[i] <= 122)))){ ++nonAlphaCounter; }
                switchCase(userInput[i], i - nonAlphaCounter);
            }
            printf("\n");
            free(userInput);
            break;
    }
}