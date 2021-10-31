#include "resumestate.h"

bool corechecker(char *filename){
	if( access(filename, F_OK) != -1 ){
		return true;
	}else{
		return false;
	}
}

void corewrite(char *filename, int s4, int s5,
                int s6, int s7, int s8){
	FILE *file1;
	file1=fopen(filename, "w");
	fprintf(file1,"%d\n%d\n%d\n%d\n%d\n",s4,s5,s6,s7,s8);
	fclose(file1);
}

void coreread(char *filename, int *s4, int *s5,
                int *s6, int *s7, int *s8){
	FILE *file1;
	file1=fopen(filename, "r");
	char text[255];
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