#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>
#include "utilities.h"

char * getField(char * target, FILE * input, int * length){
    int i = 0;

    //Read a string from the specified input stream
    do{
        target[i] = (char)fgetc(input);
        i++;
        target = realloc(target, sizeof(char) * (i + 1));
    }while(!(target[i - 1] == '\n' || target[i - 1] == '\r' || feof(input)));

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

void processLine(int lineLength, const char * line, FILE * outPutStream){
    int nonAlphaCounter = 0;
    for (int i = 0; i < lineLength; ++i) {
        if (!(((line[i] >= 65) && (line[i] <= 90)) || ((line[i] >= 97) && (line[i] <= 122)))) { ++nonAlphaCounter; }
        if(line[i] == '\0') fprintf(outPutStream, "\n");
        switchCase(line[i], i - nonAlphaCounter, outPutStream);
    }
    fprintf(outPutStream, "\n");
}

void switchCase(char character, int index, FILE * outputStream){
    //Every other character needs to be upper case, and every other character + 1 needs to be lower case
    if(index % 2) { fprintf(outputStream, "%c", toupper(character)); }
    else{ fprintf(outputStream, "%c", tolower(character)); }
}

int validateMenuOptions(int rangeStart, int rangeEnd, const char * input){
    if(strtol(input, NULL, 10) >= rangeStart && strtol(input, NULL, 10) <= rangeEnd){ return 1; }
    else{ return 0; }
}