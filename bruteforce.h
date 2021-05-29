#ifndef BRUTEFORCE_H_INCLUDED
#define BRUTEFORCE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

/*
Begin distributed bruteforce
    Input
        Character length to bruteforce -> int
        Core/thread rank -> int -> MPI_Comm_rank()
        Size/total amount of core -> int -> MPI_Comm_size()
        Test data -> *char
    Output
        Iteration of bruteforce string
*/
void bruteforce(int length, int rank, int size, char *test);

/*
Convert array of progress index to progress text
    Input
        Progress Index -> *char
        Dictionary -> *char
        Character length -> int
    Output
        Progress text -> *char
*/
void indexToText(int *idxProgress, char *progress, char *dict, int length);

/*
Count length of given progress text
    Input
        Progress text -> *char
        Maximum length of progresstext -> int;
    Output
        Calculated progress length -> return -> int
*/
int progressLen(char *progress, int maxlen);

/*
Compare progress text with test data
    Input
        Progress text -> *char
        Test data -> *char
        Algorithm length -> int (md5 = 33)
    Output
        Progress text and test valid -> 1 -> return
        Not valid -> 0 -> return
*/
int compareResult(char *progress, char *test, int algorithmLen);

/*
Supress output of a given function
    Input
        function()
    Output
        function running without message
*/
#define Q_CALL(function) {\
	FILE* tmp = stderr;\
	stderr = tmpfile();\
	(function);\
	fclose(stderr);\
	stderr = tmp;\
}

#endif