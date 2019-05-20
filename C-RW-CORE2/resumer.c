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

void corewrite(char *filename, float s123, int s4, int s5,
                 int s6, int s7, int s8){
	FILE *file1;
	file1=fopen(filename,"w");
	fprintf(file1,"%f\n%d\n%d\n%d\n%d\n%d",s123,s4,s5,s6,s7,s8);
	fclose(file1);
}

void coreread(char *filename, float *s123, int *s4, int *s5,
		 int *s6, int *s7, int *s8){
	FILE *file1;
	file1=fopen(filename,"r");
	char text[255];
	fgets(text,sizeof(text),file1);
		*s123 = atof(text);
	fgets(text,sizeof(text),file1);
		*s4 = atoi(text);
	fgets(text,sizeof(text),file1);
		*s5 = atoi(text);
	fgets(text,sizeof(text),file1);
		*s6 = atoi(text);
	fgets(text,sizeof(text),file1);
		*s7 = atoi(text);
	fgets(text,sizeof(text),file1);
		*s8 = atoi(text);
	fclose(file1);
}

void main(){
	int s8=0,s7=0,s6=0,s5=0,s4=0;
	float s123=0;
	//write files
	if(corechecker(rsmcfg) == 0){
		corewrite(rsmcfg,123,4,5,6,7,8);
	}
	//read files
	if(corechecker(rsmcfg) != 0){
		coreread(rsmcfg,&s123,&s4,&s5,&s6,&s7,&s8);
	}
	printf("%f %d %d %d %d %d\n",s123,s4,s5,s6,s7,s8);
}
