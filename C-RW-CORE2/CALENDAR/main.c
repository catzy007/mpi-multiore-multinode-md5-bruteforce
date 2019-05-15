#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "core.h"
#include "iface.h"

int main(){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int month=tm.tm_mon+1;
	int year=tm.tm_year+1900;
	int dd,mm,yy,rmline;
	char selection;
	char selection2;
	char dummy;
	char keyword[255];

	ifacewelcomescr();
	
	//if database.cfg not exist
	corewrite("\0");
	
	loop1:
	system("clear");
	
	ifaceshow(month,year);	
	
	printf("1. Bulan Berikutnya\n");
	printf("2. Bulan Sebelumnya\n");
	printf("3. Tampilkan Kegiatan\n");
	printf("4. Tambah Kegiatan\n");
	printf("5. Cari Kegiatan\n");
	printf("6. Hapus Kegiatan\n");
	printf("7. Tampilkan Seluruh Kegiatan\n");
	printf("8. Urutkan Kegiatan\n");
	printf("9. Keluar Program\n");
	
	printf("\nMasukkan Pilihan Anda : ");
	scanf("%c",&selection);
	getc(stdin);
	
	switch(selection) {
      case '1' :
         month+=1;
         if(month>=12){
			 year+=1;
			 month=1;
		 }
		 selection='x';
         goto loop1;
      case '2' :
		 month-=1;
         if(month<1){
			 year-=1;
			 month=12;
		 }
		 selection='x';
		 goto loop1;
	  case '3' :
	     loop2:
	     system("clear");
         ifaceshow(month,year);
         printf("1. Menuju Bulan Berikutnya\n");
	     printf("2. Menuju Bulan Sebelumnya\n");
	     printf("3. Tampilkan Kegiatan Pada Bulan ini\n");
	     printf("4. Kembali\n");
	     printf("\nMasukkan Pilihan Anda : ");
	     scanf("%c",&selection2);
	     getc(stdin);
	     switch(selection2){
			case '1' :
				month+=1;
				if(month>=12){
					year+=1;
					month=1;
				}
				goto loop2;
			case '2' :
				month-=1;
				if(month<1){
					year-=1;
					month=12;
				}
				goto loop2;
			case '3' :
				system("clear");
				ifaceshow(month,year);
				printf("Pilih Tanggal : ");
				scanf("%d",&dd);
				puts("");
				ifacefindataprint(dd,month,year);
				printf("\nPress Enter to Continue . . . ");
				scanf("%c",&dummy);
				getc(stdin);
				goto loop2;
			case '4' : 
				month=tm.tm_mon+1;
				year=tm.tm_year+1900;
				selection='x';
				goto loop1;
			default : 
			    getc(stdin);
				goto loop2;
		 }
      case '4' :
         system("clear");
         ifaceshow(month,year);
         ifaceformdata();
         printf("\nPress Enter to Continue . . . ");
         scanf("%c",&dummy);
         selection='x';
		 goto loop1;
      case '5' :
         system("clear");
         ifaceshow(month,year);
         printf("Inputkan Keyword Anda : ");
         fgets(keyword,255,stdin);
         strtok(keyword, "\n");
         corefind(keyword);
         printf("\nPress Enter to Continue . . . ");
         scanf("%c",&dummy);
         selection='x';
         goto loop1;
      case '6' :
         system("clear");
         ifaceshow(month,year);
         coreread();
         printf("\nInputkan line index yang ingin dihapus : ");
         scanf("%d",&rmline);
         getc(stdin);
         corermline(rmline);
         printf("\nPress Enter to Continue . . . ");
         scanf("%c",&dummy);
         selection='x';
         goto loop1;
      case '7' :
         system("clear");
         ifaceshow(month,year);
         coreread();
         printf("\nPress Enter to Continue . . . ");
         scanf("%c",&dummy);
         selection='x';
         goto loop1;
      case '8' :
         system("clear");
         ifaceshow(month,year);
         coresort();
         coreread();
         printf("\nPress Enter to Continue . . . ");
         scanf("%c",&dummy);
         selection='x';
         goto loop1;
      case '9' :
         return 0;
      default :
         selection='x';
         getc(stdin);
         goto loop1;
	}
	return 0;
}
