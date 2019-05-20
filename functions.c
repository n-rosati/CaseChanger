#include <stdio.h>
#include <malloc.h>
#include "functions.h"

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