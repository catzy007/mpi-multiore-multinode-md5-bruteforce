#include "resumer.h"

int corechecker(char *filename){
	if( access(filename, F_OK) != -1 ){
		return 1;
	}else{
		return 0;
	}
}

void corewrite(char *filename, int s4, int s5,
                 int s6, int s7, int s8){
	FILE *file1;
	file1=fopen(filename,"w");
	fprintf(file1,"%d\n%d\n%d\n%d\n%d",s4,s5,s6,s7,s8);
	fclose(file1);
}

void coreread(char *filename, int *s4, int *s5,
		 int *s6, int *s7, int *s8){
	FILE *file1;
	file1=fopen(filename,"r");
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

/*
//example usage
void main(){
	int s4=0,s5=0,s6=0,s7=0,s8=0;

	//write files
	if(corechecker(rsmcfg) == 0){
		corewrite(rsmcfg,4,5,6,7,8);
	}

	//read files
	if(corechecker(rsmcfg) != 0){
		coreread(rsmcfg,&s4,&s5,&s6,&s7,&s8);
	}else{
		s4=0; s5=0;
		s6=0; s7=0;
		s8=0;
	}

	printf("%d %d %d %d %d\n",s4,s5,s6,s7,s8);
}
*/
