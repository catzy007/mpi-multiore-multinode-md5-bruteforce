#ifndef IFACE_H_INCLUDED
#define IFACE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int dd;
  int mm;
  int yy;
}Tanggal;

typedef struct{
  int jam;
  int menit;
}Waktu;

typedef struct{
  char kegiatan[255];
  char nama[255];
  Tanggal Tgl;
  Waktu Wkt;
}Record;

void ifacegetdata(int day,int month,int year);
void ifacefindataprint(int day,int month,int year);
void ifaceshow(int month,int year);
void ifaceprintmark(int day,int month,int year);
void ifaceformdata(void);
void ifacewelcomescr(void);

#endif
