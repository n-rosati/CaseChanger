#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "utilities.h"

int main(){
    char * userInput;
    int sourceLocation;
    int destinationLocation;
    int userInputLength;

    //Input location selection
    int firstRun = 1;
    do{
        printf("Select source location:\n");
        printf("1. Read from console\n2. Read from file\n");
        userInput = getField(malloc(sizeof(char)), stdin, &userInputLength);
        if(validateMenuOptions(1, 2, userInput)){
            if(firstRun){ clearLine(4); }
            else{ clearLine(5); }
            sourceLocation = strtol(userInput, NULL, 10);
            free(userInput);
            break;
        }
        else{
            //This re-prompts the user for input if what they entered is invalid, without spamming the console history
            if(firstRun){
                clearLine(4);
                printf("Invalid input.\n");
                firstRun = 0;
            }
            else{
                clearLine(5);
                printf("Invalid input.\n");
            }
        }
        free(userInput);
    }while(1);

    //Output location selection
    do{
        if(userInput != NULL){ free(userInput); }
        printf("Select destination location:\n");
        printf("1. Console\n2. New File\n");
        userInput = getField(malloc(sizeof(char)), stdin, NULL);
    }while(!validateMenuOptions(1, 2, userInput));
    destinationLocation = strtol(userInput, NULL, 10);

    switch(sourceLocation){
        case 1: {
            //Input from console
            switch (destinationLocation) {
                case 1: {
                    //Console output
                    userInput = getField(malloc(sizeof(char)), stdin, &userInputLength);
                    clearLine(1);
                    processLine(userInputLength, userInput, stdout);
                    free(userInput);
                    break;
                }
                case 2: {
                    //File output
                    //Get file path and create a new file path with "-altered" appended to it
                    printf("Enter the path to the file:\n");
                    int pathLength;
                    char *filePath = getField(malloc(sizeof(char)), stdin, &pathLength);
                    clearLine(2);
                    char *newFilePath = calloc(pathLength + 9, sizeof(char));
                    strncpy(newFilePath, filePath, pathLength - 4);
                    strcat(newFilePath, "-altered.txt\0");

                    //Open the destination file
                    FILE *newFile = fopen(newFilePath, "w");
                    if (newFile == NULL) {
                        printf("The following error occurred opening the destination file: %s", strerror(errno));
                        return -2;
                    }

                    break;
                }
            }
            break;
        }
        case 2: {
            //Input from file
            //Open the source file
            printf("Enter the path to the file:\n");
            int pathLength;
            char *filePath = getField(malloc(sizeof(char)), stdin, &pathLength);

            FILE *file = fopen(filePath, "r");
            if (file == NULL) {
                printf("The following error occurred opening the source file: %s", strerror(errno));
                return -1;
            }
            switch(destinationLocation){
                case 1: {
                    //Console output
                    //Read the old file, adjust casing, print to console
                    int lineLength;
                    do {
                        char *currentLine = getField(malloc(sizeof(char)), file, &lineLength);
                        processLine(lineLength, currentLine, stdout);
                        free(currentLine);
                    } while (!feof(file));
                    break;
                }
                case 2:{
                    //File output
                    //TODO
                    break;
                }
            }
            fclose(file);
            free(filePath);
            break;
        }
    }
    return 0;
}