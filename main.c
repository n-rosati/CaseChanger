#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
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
            //This re-prompts the user for input if what they entered is invalid, without spamming the console history
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

    switch(sourceOption){ // NOLINT(hicpp-multiway-paths-covered)
        case 1:
            //Read from console input, adjust casing, write to console output
            userInput = getField(malloc(sizeof(char)), stdin, &userInputLength);
            processLine(userInputLength, userInput, stdout);
            free(userInput);
            break;

        case 2:
            printf("Enter the path to the file:\n");
            //Get file path and create a new file path with "-altered" appended to it
            int pathLength;
            char * filePath = getField(malloc(sizeof(char)), stdin, &pathLength);
            clearLine(2);

            char * newFilePath = calloc(pathLength + 9, sizeof(char));
            strncpy(newFilePath, filePath, pathLength - 4);
            strcat(newFilePath, "-altered.txt\0");

            //Open the new files
            FILE * file = fopen(filePath, "r");
            if(file == NULL){
                fprintf(stdout, "The following error occurred opening the source file: %s", strerror(errno));
                return -1;
            }
            FILE * newFile = fopen(newFilePath, "w");
            if(newFile == NULL){
                fprintf(stdout, "The following error occurred opening the destination file: %s", strerror(errno));
                fclose(file);
                return -2;
            }

            //Read the old file, adjust casing, print to console
            //TODO: Write to user specified destination
            int lineLength;
            do{
                char * currentLine = getField(malloc(sizeof(char)), file, &lineLength);
                if(strlen(currentLine) == 0){ printf("\n"); continue; }
                processLine(lineLength, currentLine, stdout);
                free(currentLine);
            }while(!feof(file));

            free(filePath);
            free(newFilePath);
            break;
    }

    return 0;
}