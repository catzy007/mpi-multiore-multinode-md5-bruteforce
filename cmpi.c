#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "openssl/md5.h"

char rsmcfg[]="resumestate.cfg";

//compile with mpicc cmpi.c -o cmpi -lcrypto
//this test program uses md5 library from openssl
//https://github.com/openssl/openssl/tree/master/include/openssl

//this program support up to 238328 core

//some code to silently call function without error message
//thanks to https://stackoverflow.com/questions/4760201/how-do-i-suppress-output-while-using-a-dynamic-library
#define Q_CALL(function) {\
	FILE* tmp = stderr;\
	stderr = tmpfile();\
	(function);\
	fclose(stderr);\
	stderr = tmp;\
}

//string to md5 function
//thanks to https://stackoverflow.com/questions/7627723/how-to-create-a-md5-hash-of-a-string-in-c
char *strMD5(const char *str, int length, char *out){
	int n;
	MD5_CTX c;
	unsigned char digest[16];
	//char *out=(char*)malloc(33); //turn this into parameter for better memory management
	MD5_Init(&c);
	while(length>0){
		if(length>512){
			MD5_Update(&c,str,512);
		}else{
			MD5_Update(&c,str,length);
		}
		length-=512;
		str+=512;
	}
	MD5_Final(digest,&c);
	for(n=0;n<16;++n){
		snprintf(&(out[n*2]),16*2,"%02x",(unsigned int)digest[n]);
	}
	return out;
}


int corechecker(char *filename);

void corewrite(char *filename, int s4, int s5, int s6, int s7, int s8);

void coreread(char *filename, int *s4, int *s5, int *s6, int *s7, int *s8);

void datetime(void){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("Date : %.2d/%.2d/%d - %.2d:%.2d:%.2d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

int main(int argc, char **argv){
//put your md5 data below
	char data[]="dd1e0ce7213d62e65b7bc7a89084f413"; //testcase or md5 data you want to break
	int dataLen=sizeof(data)/sizeof(char); //md5 need 33 character. Can be changed to other algorithm if needed

//some variables
	char dict[]="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; //dictionary. add more or reduce as needed
	int step=8; //currently this program support 8 step. Change this value and add more loop if needed
	int dictLen=(sizeof(dict)/sizeof(char))-1; //default is 62 character
	int rank,tst,processor; //variables to store mpi value
	int i,j,mark=0; ///loop variables for comparator
	int s1,s2,s3,s4,s5,s6,s7,s8; //loop variables for key generator
	float s123,Ms123=(dictLen*dictLen*dictLen); //another loop variables for key generator
	char *temp=malloc(sizeof(char)*step); //temporary variables for generated key
	char *out=malloc(sizeof(char)*dataLen); //temporary0 md5 hash
	char *hash; //temporary1 md5 hash

//get value from resumer config
	//temporary var
	int t4, t5, t6, t7, t8;

	//getter
        if(corechecker(rsmcfg) != 0){
                coreread(rsmcfg, &t4, &t5, &t6, &t7, &t8);
        }else{
                t4=0; t5=0; t6=0;
                t7=0; t8=0;
        }

//initializing MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &processor); //get the core count
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //get the core rank

	//line below for master node
	if(rank==0){
		printf("MPI MD5 BREAKER\nCore : %d\n",processor);
		datetime();
		printf("Data : %s\n",data);
		printf("Hello From Core %.2d\n",rank);
		//printf("%d %d\n",dictLen,dataLen); //debug_line_can_be_removed
		for(i=1;i<processor;i++){
			MPI_Recv(&tst,1,MPI_INT,i,1033,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("Hello From Core %.2d\n",tst);
		}
	}

//mpi algorithm begin
	//preparing all core
	for(i=1;i<processor;i++){
		if(rank==i){
			MPI_Send(&rank,1,MPI_INT,0,1033,MPI_COMM_WORLD);
		}
	}
	for(i=0;i<processor;i++){
		if(rank==i){
		//key generator algorithm begin
		 for(s8=t8; s8<dictLen; s8++){
		  for(s7=t7; s7<dictLen; s7++){
		   for(s6=t6; s6<dictLen; s6++){
		    for(s5=t5; s5<dictLen; s5++){
		     for(s4=t4; s4<dictLen; s4++){
		      //write to resumer config
		      if(rank==0){
		       corewrite(rsmcfg,s4,s5,s6,s7,s8);
		      }
		      for(s123=i; s123<Ms123; s123+=processor){ //62^3=238328
		       s1=abs(s123)%dictLen;
		       s2=abs(s123/dictLen)%dictLen;
		       s3=abs(s123/dictLen/dictLen)%dictLen;
			temp[0]=dict[s1];
			temp[1]=dict[s2];
			temp[2]=dict[s3];
			temp[3]=dict[s4];
			temp[4]=dict[s5];
			temp[5]=dict[s6];
			temp[6]=dict[s7];
			temp[7]=dict[s8];
			hash=strMD5(temp,step,out);
			//printf("%s %s %d=%c %d=%c %d=%c\n",temp,hash,s1,dict[s1],s2,dict[s2],s3,dict[s3]); //debug_line_can_be_removed
			//printf("%.2d %s %s\n",rank,temp,hash); //debug_line_can_be_removed
			//comparator algorithm begin
			for(j=0;j<dataLen;j++){
				if(hash[j]==data[j]){
					mark++;
				}else if(hash[j]!=data[j]){
					break;
				}
			}
			if(mark==dataLen){
				goto finalize;
			}else{
				mark=0;
			}
		      }//s123
		     }//s4
		    }//s5
		   }//s6
		  }//s7
		 }//s8
			if(mark==dataLen){
				finalize:
				datetime();
				printf("Core %.2d - The Result Was : %s\nDone!\n",rank,temp);
				free(hash);free(temp);
				Q_CALL(MPI_Abort(MPI_COMM_WORLD,MPI_SUCCESS)); //keep using mpi abort until find better solution
			}
		}
	}

	MPI_Finalize();
	return 0;
}

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
