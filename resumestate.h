#ifndef RESUMESTATE_H_INCLUDED
#define RESUMESTATE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

/*
Check if file is exist
    Input
        filename -> string
    Output
        true -> file exist
        false -> file missing
*/
bool corechecker(char *filename);

/*
Write current progress to file
    Input
        filename -> string
        step 4,5,6,7,8 -> int
    Output
        progress file
*/
void corewrite(char *filename, int s4, int s5, int s6, int s7, int s8);

/*
Read last progress from file
    Input
        filename -> string
    Output
        step 4,5,6,7,8 -> &int
*/
void coreread(char *filename, int *s4, int *s5, int *s6, int *s7, int *s8);

#endif