#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include "utilities.h"

char * getField(char * target, FILE * input, int * length){
    int i = 0;

    //Read a string from the specified input stream
    do{
        target[i] = (char)fgetc(input);
        i++;
        target = realloc(target, sizeof(char) * (i + 1));
    }while(!((int)target[i - 1] == 13 || (int)target[i - 1] == 10 || (int)target[i - 1] == -1));

    //Properly terminate the string
    target[i - 1] = '\0';

    //'Return' the length if needed
    if(length != NULL){ *length = i - 1; }

    return target;
}

void clearLine(int numberOfLinesToClear){
    for (int i = 0; i < numberOfLinesToClear; ++i)
        //Clears the line the cursor is on and then moves the cursor up a line
        fprintf(stdout, "\033[A\33[2K\r");
}

void processLine(int lineLength, const char * line){
    int nonAlphaCounter = 0;
    for (int i = 0; i < lineLength; ++i) {
        if (!(((line[i] >= 65) && (line[i] <= 90)) || ((line[i] >= 97) && (line[i] <= 122)))) { ++nonAlphaCounter; }
        switchCase(line[i], i - nonAlphaCounter);
    }
    printf("\n");
}

void switchCase(char character, int index){
    //Every other character needs to be upper case, and every other character + 1 needs to be lower case
    if(index % 2) {
        printf("%c", toupper(character));
    }
    else{
        printf("%c", tolower(character));
    }
}