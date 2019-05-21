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
    }while(!(target[i - 1] == '\n' || target[i - 1] == '\0'));

    //Properly terminate the string
    target[i - 1] = '\0';

    //'Return' the length if needed
    if(length != NULL){ *length = i - 1; }

    return target;
}

void clearLines(int numberOfLinesToClear){
    for (int i = 0; i < numberOfLinesToClear; ++i)
        //Clears the line the cursor is on and then moves the cursor up a line
        fprintf(stdout, "\033[A\33[2K\r");
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