#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "utilities.h"

int main(){
    char * userInput;
    int sourceOption;
    int userInputLength;

    //Get user input
    int firstRun = 1;
    do{
        printf("1. Read from console\n2. Read from file\n");
        userInput = getField(malloc(sizeof(char)), stdin, &userInputLength);
        if((userInputLength == 1) && ((int)userInput[0] == 49 || (int)userInput[0] == 50)){
            if(firstRun){ clearLine(3); }
            else{ clearLine(4); }
            sourceOption = (int)userInput[0] - 48;
            free(userInput);
            break;
        }
        else{
            //This re-prompts the user for input if what they entered is invalid, without spamming the console
            if(firstRun){
                clearLine(3);
                printf("Invalid input.\n");
                firstRun = 0;
            }
            else{
                clearLine(4);
                printf("Invalid input.\n");
            }
        }
        free(userInput);
    }while(1);

    switch(sourceOption){
        case 1:
            userInput = getField(malloc(sizeof(char)), stdin, &userInputLength);
            int nonAlphaCounter = 0;
            for (int i = 0; i < userInputLength; ++i) {
                if(!(((userInput[i] >= 65) && (userInput[i] <=90)) || ((userInput[i] >= 97) && (userInput[i] <= 122)))){ ++nonAlphaCounter; }
                switchCase(userInput[i], i - nonAlphaCounter);
            }
            printf("\n");
            free(userInput);
            break;
    }
}