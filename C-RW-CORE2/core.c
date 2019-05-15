#include "core.h"

//write data (string) to database.cfg
void corewrite(char *string){
  FILE *file1;
  file1=fopen("database.cfg","a+");
  fprintf(file1,"%s",string);
  fclose(file1);
}

//read data from database.cfg line by line
void coreread(){
  FILE *file1;
  file1=fopen("database.cfg","r");
  char text[255];
  int loop=1;
  while(fgets(text,sizeof(text),file1)!= NULL){
    printf("%.2d - %s",loop++,text);
  }
  fclose(file1);
}

//delete specific line based on index (index started from 1)
void corermline(int rmline){
  FILE *file1, *file2;
  char text[255];
  int loop=1;
  file1=fopen("database.cfg","r");
  file2=fopen("dbtemp.cfg","w");
  while(fgets(text,sizeof(text),file1)!= NULL){
    if(loop!=rmline){
      fprintf(file2,"%s",text);
    }
    loop++;
  }
  fclose(file1);
  fclose(file2);
  remove("database.cfg");
  rename("dbtemp.cfg","database.cfg");
}

//find data from database.cfg
void corefind(char *search){
  printf("Record Found\n");
  FILE *file1;
  file1=fopen("database.cfg","r");
  char text[255];
  int loop=1;
  int count=0;
  int idx=0;
  while(search[count]!='\0'){
    count++;
  }
  int n,m,min,max=count,true;
  while(fgets(text,sizeof(text),file1)!= NULL){
	n=0;
	m=0;
	true=0;
	min=0;
	max=count-1;
    while(text[max]!='\0'){
      n=0;
      m=min;
      true=0;
      while(search[n]!='\0'){
        //printf("%c %c\n",search[n],text[m]); //debug_line_can_be_deleted
        if(search[n]==text[m]){
          //printf("-%c %c\n",search[n],text[m]); //debug_line_can_be_deleted
          true++;
        }
        m++;
        n++;
      }
      if(true==count){
		idx++;
        printf("%.2d %s",idx,text);
      }
      min++;
      max++;
    }
    //printf("%d - %s",loop++,text); //debug_line_can_be_deleted
  }
  fclose(file1);
}

//sort database.cfg based on date (8 digit from each line)
void coresort(){
  printf("Sorting Begin\n");
  FILE *file1, *file2;
  char text[255];
  int loop,i;
  
  //count line number of database.cfg
  file1=fopen("database.cfg","r");
  int linecount=0;
  while(fgets(text,sizeof(text),file1)!= NULL){
    linecount++;
  }
  fclose(file1);
  
  //convert 8 digit of each line to integer
  //ptrint = pointerinteger
  int **ptrint=malloc(sizeof(int*)*linecount);
  char ptrnbr[9]={'\0'};
  file1=fopen("database.cfg","r");
  loop=0;
  while(loop<linecount){
	fgets(text,sizeof(text),file1);
	memcpy(ptrnbr,text,8);
    ptrint[loop]=malloc(sizeof(int));
    *ptrint[loop]=atoi(ptrnbr);
	loop++;
  }
  fclose(file1);
  
  //copy each line of database.cfg to heap memory
  //ptrtext = pointertext
  char **ptrtext=malloc(sizeof(char*)*(linecount));
  file1=fopen("database.cfg","r");
  loop=0;
  while(loop<linecount){
	fgets(text,sizeof(text),file1);
	ptrtext[loop]=malloc(sizeof(text));
	memcpy(ptrtext[loop],text,sizeof(text));
	loop++;
  }
  fclose(file1);
  
  //modified selection sort algorithm begin
  int m=0,n=0;
  int min;
  char *tmp;
  for(n=0;n<linecount;n++){
    min=n;
    for(m=n+1;m<linecount;m++){
      if(*ptrint[min]>*ptrint[m]){
        min=m;
      }
    }
    if(min!=n){
	  //swap address of ptrtext[n] and ptrtext[min]
	  tmp=ptrtext[n];
	  ptrtext[n]=ptrtext[min];
	  ptrtext[min]=tmp;
	  //swap content of ptrint[n] and ptrint[min]
	  *ptrint[n]=*ptrint[n]+*ptrint[min];
	  *ptrint[min]=*ptrint[n]-*ptrint[min];
	  *ptrint[n]=*ptrint[n]-*ptrint[min];
    }
  }

  //write sorted data to dbtemp.cfg
  file2=fopen("dbtemp.cfg","w");
  for(i=0;i<linecount;i++){
	//printf("%d %s",i,ptrtext[i]);
	fprintf(file2,"%s",ptrtext[i]);
  }
  fclose(file2);
  
  //free some memory
  for(i=0;i<linecount;i++){
    free(ptrtext[i]);
  }
  for(i=0;i<linecount;i++){
    free(ptrint[i]);
  }
  free(ptrtext);
  free(ptrint);
  remove("database.cfg");
  rename("dbtemp.cfg","database.cfg");
}

//2018 Bagus Saputra
