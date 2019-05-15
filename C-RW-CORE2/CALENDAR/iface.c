#include "iface.h"
#include "core.h"

//show welcome screeen
void ifacewelcomescr(void){
	printf("  _      __    __                     __      \n");
	printf(" | | /| / /__ / /______  __ _  ___   / /____  \n");
	printf(" | |/ |/ / -_) / __/ _ \134/  ' \134/ -_) / __/ _ \134 \n");
	printf(" |__/|__/\134__/_/\134__/\134___/_/_/_/\134__/  \134__/\134___/ \n");
	printf("  _____ _           ___      _             _          \n");
	printf(" |_   _| |_  ___   / __|__ _| |___ _ _  __| |__ _ _ _ \n");
	printf("   | | | ' \134/ -_) | (__/ _` | / -_) ' \134/ _` / _` | '_|\n");
	printf("   |_| |_||_\134___|  \134___\134__,_|_\134___|_||_\134__,_\134__,_|_|  \n");
	system("sleep 3");
	system("clear");
}

//check if form data valid
int ifacecheckform(int day, int month, int year, int jam, int menit){
	//check month
	if(month>12 || month<1){
		return 0;
	}
	//check day
	int dayscount;
	if(month==4 || month==6 || month==9 || month==11){  
		dayscount=30;  
	}else if(month==2){ 
		if((year%4==0 && year%100!=0) || (year%400==0)){  
			dayscount=29;  
		}else{ 
			dayscount=28;
		}
	}else{
		dayscount=31;
	}
	if(day>dayscount || day<1){
		return 0;
	}
	//check jam
	if(jam>24 || jam<1){
		return 0;
	}
	//check menit
	if(menit>60 || menit<1){
		return 0;
	}
	return 1;
}

//enter form data and call corewrite2
void ifaceformdata(void){
	Record Dbase;
	printf("Inputkan Tahun\t\t\t: ");
    scanf("%d",&Dbase.Tgl.yy);
    printf("Inputkan Bulan\t\t\t: ");
    scanf("%d",&Dbase.Tgl.mm);
    printf("Inputkan Tanggal\t\t: ");
    scanf("%d",&Dbase.Tgl.dd);
    printf("Inputkan Jam\t\t\t: ");
    scanf("%d",&Dbase.Wkt.jam);
    printf("Inputkan Menit\t\t\t: ");
    scanf("%d",&Dbase.Wkt.menit);
    getc(stdin);
    printf("Inputkan Nama Kegiatan\t\t: ");
    fgets(Dbase.kegiatan,255,stdin);
    strtok(Dbase.kegiatan, "\174");
    strtok(Dbase.kegiatan, "\n");
    printf("Inputkan Orang Yang Terlibat\t: ");
    fgets(Dbase.nama,255,stdin);
    strtok(Dbase.nama, "\174");
    strtok(Dbase.nama, "\n");
    if(ifacecheckform(Dbase.Tgl.dd,Dbase.Tgl.mm,Dbase.Tgl.yy,Dbase.Wkt.jam,Dbase.Wkt.menit) != 1){
		printf("Kegiatan anda tidak tersimpan! Mohon cek kembali\n");
	}else{
		printf("Kegiatan anda telah tersimpan\n");
		corewrite2(Dbase.Tgl.yy,Dbase.Tgl.mm,Dbase.Tgl.dd,Dbase.Wkt.jam,Dbase.Wkt.menit,Dbase.kegiatan,Dbase.nama);
	}
}     

//print content of record based on DD MM YYYY
void ifacegetdata(int day,int month,int year){
  Record *RecordTemp;
  RecordTemp=malloc(sizeof(Record));
  
  char temp[255];
  int nbrtemp;
  int nbr1;
  sprintf(temp,"%d%.2d%.2d",year,month,day);
  nbr1=atoi(temp);

  FILE *file1;
  char text[255];
  file1=fopen("database.cfg","r");
  int nbr2,loop=0,count=8,i,j,marken;
  RecordTemp->Tgl.dd=day;
  RecordTemp->Tgl.mm=month;
  RecordTemp->Tgl.yy=year;
  marken=0;
  while(fgets(text,sizeof(text),file1)!= NULL && marken==0){
    memcpy(temp,text,8);
    nbr2=atoi(temp);

    if(nbr1==nbr2){
	  marken=1;
  //Algorithm to get time from database
	  count+=1;
      for(i=0;i<255;i++){
        temp[i]='\0';
      }
	  i=0;
	  for(i=0;i<2;i++,count++){
        temp[i]=text[count];
	  }
	  nbrtemp=atoi(temp);
      RecordTemp->Wkt.jam=nbrtemp;
	  for(i=0;i<2;i++,count++){
        temp[i]=text[count];
      }
      nbrtemp=atoi(temp);
      RecordTemp->Wkt.menit=nbrtemp;
      
  //Algorithm to get "kegiatan" from database
      count+=1;
      for(i=0;i<255;i++){
        temp[i]='\0';
      }
	  i=0;
      while(text[count]!='\174'){
        //printf("%c ",text[count]); //debug_line_can_be_deleted
        temp[i]=text[count];
        i++;
        count++;
      }
      //printf(" %s \n",temp); //debug_line_can_be_deleted
      strcpy(RecordTemp->kegiatan,temp);
      
  //Algorithm to get nama from database
      count+=1;
      for(i=0;i<255;i++){
        temp[i]='\0';
      }
	  i=0;
      while(text[count]!='\174'){
        //printf("%c ",text[count]); //debug_line_can_be_deleted
        temp[i]=text[count];
        i++;
        count++;
      }
      //printf(" %s \n",temp); //debug_line_can_be_deleted
      strcpy(RecordTemp->nama,temp);
    }
  }
  printf("Pada Tanggal\t\t: %.2d %.2d %d\n",(*RecordTemp).Tgl.dd,(*RecordTemp).Tgl.mm,(*RecordTemp).Tgl.yy);
  printf("Pukul\t\t\t: %.2d.%.2d\n",(*RecordTemp).Wkt.jam,(*RecordTemp).Wkt.menit);
  printf("Kegiatan\t\t: %s\n",(*RecordTemp).kegiatan);
  printf("Orang Yang Terlibat\t: %s\n",(*RecordTemp).nama);
}

//check if input date exist on database.cfg then call ifacegetdata
void ifacefindataprint(int day,int month,int year){
  FILE *file1;
  char text[255];
  char strnbr1[9];
  char strnbr2[9];
  int intnbr1;
  int intnbr2;
  
  //join input date as 1 data
  sprintf(strnbr1,"%d%.2d%.2d",year,month,day);
  intnbr1=atoi(strnbr1);
  //printf("%d\n",intnbr1); //debug_line_can_be_deleted
  
  //check if input date exist in database.cfg call ifacegetdata
  file1=fopen("database.cfg","r");
  while(fgets(text,sizeof(text),file1)!= NULL){
    memcpy(strnbr2,text,8);
    intnbr2=atoi(strnbr2);
    //printf("%d %d\n",intnbr1,intnbr2); //debug_line_can_be_deleted
    if(intnbr1==intnbr2){
      ifacegetdata(day,month,year);
      fclose(file1);
      return;
    }
  }
  //if data wasn't found
  printf("Data Tidak Ditemukan!\n");
  fclose(file1);
}

//check if input date exist on database.cfg then print * mark
void ifaceprintmark(int day,int month,int year){
  FILE *file1;
  char text[255];
  char strnbr1[9];
  char strnbr2[9];
  int intnbr1;
  int intnbr2;
  
  //join input date as 1 data
  sprintf(strnbr1,"%d%.2d%.2d",year,month,day);
  intnbr1=atoi(strnbr1);
  //printf("%d\n",intnbr1); //debug_line_can_be_deleted
  
  //check if input date exist in database.cfg and print "*" mark
  file1=fopen("database.cfg","r");
  while(fgets(text,sizeof(text),file1)!= NULL){
    memcpy(strnbr2,text,8);
    intnbr2=atoi(strnbr2);
    //printf("%d %d\n",intnbr1,intnbr2); //debug_line_can_be_deleted
    if(intnbr1==intnbr2){
      printf("*");
      fclose(file1);
      return;
    }
  }
  printf(" ");
  fclose(file1);
}

//print calendar based on month and year
void ifaceshow(int month,int year){
  int year1=year;
  int month1=month;
  //print current month and year
  char months[12][10]={"January","February","March","April","May",
  "June","July","August","September","Oktober","November","December"};
  printf("  %s %d\n",months[month1-1],year);

  //calculate count of day in specified months
  int dayscount;
  if(month==4 || month==6 || month==9 || month==11){  
    dayscount=30;  
  }else if(month==2){ 
    if((year%4==0 && year%100!=0) || (year%400==0)){  
      dayscount=29;  
    }else{ 
      dayscount=28;
    }
  }else{
    dayscount=31;
  }
  
  //calculate what day of 1st in specified months
  int dayofweek=((year-=month<3)+year/4-year/100+year/400+"-bed=pen+mad."[month]+1)%7;
  //printf("%d %d\n",dayscount,dayofweek); //debug_line_can_be_removed
  
  //print the calendar
  int i,j;
  printf("  SUN  MON  TUE  WED  TRU  FRI  SAT\n");
  for(i=1,j=1;i<=dayscount+dayofweek;i++){
    if(i>dayofweek){
      printf("  %2.d",j);
      //call ifaceprintmark
      ifaceprintmark(j,month1,year1);
      if(i%7==0 && i<dayscount+dayofweek){
        puts("");
      }
      j++;
    }else{
      printf("     ");
    }
  }
  puts("\n");
}
