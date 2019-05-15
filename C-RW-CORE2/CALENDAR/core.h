#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void corewrite(char *string);
void corewrite2(int yy, int mm, int dd, int jam, int menit, char *kegiatan, char *nama);
void coreread();
void corermline(int rmline);
void corefind(char *search);
void coresort();

#endif
