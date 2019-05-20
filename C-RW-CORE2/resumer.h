#ifndef RESUMER_H_INCLUDED
#define RESUMER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char rsmcfg[]="resumestate.cfg";

int corechecker(char *filename);
void corewrite(char *filename, int s4, int s5,
		int s6, int s7, int s8);
void coreread(char *filename, int *s4, int *s5,
		int *s6, int *s7, int *s8);

#endif
