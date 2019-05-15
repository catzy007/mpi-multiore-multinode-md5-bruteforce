#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char rsmcfg[]="resumestate.cfg";

int corechecker(char *filename){
	if( access(filename, F_OK) != -1 ){
		return 1;
	}else{
		return 0;
	}
}

void corewrite(char *string, char *filename){
  FILE *file1;
  file1=fopen(filename,"w");
  fprintf(file1,"%s",string);
  fclose(file1);
}

void coreread(char *filename){
  FILE *file1;
  file1=fopen(filename,"r");
  char text[255];
  int loop=1;
  while(fgets(text,sizeof(text),file1)!= NULL){
    printf("%.2d - %s",loop++,text);
  }
  fclose(file1);
}

void main(){
	if(corechecker(rsmcfg) == 0){
		corewrite("0\n0\n0\n0\n0", rsmcfg);
	}
	//printf("%s\n",corechecker(rsmcfg)?"exist":"not");
}
