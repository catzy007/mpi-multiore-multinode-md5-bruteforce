#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "openssl/md5.h"

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

void datetime(void){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("Date : %.2d/%.2d/%d - %.2d:%.2d:%.2d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

int main(int argc, char **argv){
//some variables
	int rank,tst; //variable to store rank
	int processor; //amount of cores
	int i,j,mark=0; ///loop variable
	int s1a,s2a,s1,s2,s3,s4,s5,s6,s7,s8,step=8;float s123; //loop variables for key generator
	char temp[9]={'\0'}; //temporary variables for generated key (n+1)
	char *out=malloc(sizeof(char)*33); //temporary0 md5 hash
	char *hash; //temporary1 md5 hash
	char dict[62]="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; //dictionary

	char data[]="b5320b498808358b19baeb67bc43eb8b"; //testcase

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
		for(i=1;i<processor;i++){
			MPI_Recv(&tst,1,MPI_INT,i,1033,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("Hello From Core %.2d\n",tst);
		}
	}

//mpi algorithm begin
	//testing all core
	for(i=1;i<processor;i++){
		if(rank==i){
			//printf("Hello From Core %.2d\n",rank);
			MPI_Send(&rank,1,MPI_INT,0,1033,MPI_COMM_WORLD);
		}
	}
	for(i=0;i<processor;i++){
		if(rank==i){
			//key generator algorithm begin
			for(s8=0;s8<62;s8++){
			for(s7=0;s7<62;s7++){
			for(s6=0;s6<62;s6++){
			for(s5=0;s5<62;s5++){
			for(s4=0;s4<62;s4++){
			for(s123=i;s123<pow(62,3);s123+=processor){ //62^3=238328
			s1=abs(s123)%62;
			s2=abs(s123/62)%62;
			s3=abs(s123/62/62)%62;
				temp[0]=dict[s8];
				temp[1]=dict[s7];
				temp[2]=dict[s6];
				temp[3]=dict[s5];
				temp[4]=dict[s4];
				temp[5]=dict[s3];
				temp[6]=dict[s2];
				temp[7]=dict[s1];
				hash=strMD5(temp,step,out);
				//printf("%.0f %s %s %d=%c %d=%c\n",s123,temp,hash,s2,dict[s2],s1,dict[s1]); //debug_line_can_be_removed
				//system("sleep 1");
				//printf("%.2d %s %s\n",rank,temp,hash); //debug_line_can_be_removed
				//comparator algorithm begin
				for(j=0;j<33;j++){
					if(hash[j]==data[j]){
						mark++;
					}else if(hash[j]!=data[j]){
						break;
					}
				}
				if(mark==33){
					goto finalize0;
				}else{
					mark=0;
				}
			}//s123
			}//s4
			}//s5
			}//s6
			}//s7
			}//s8
			if(s8<62 && mark==33){
				finalize0:
				datetime();
				printf("Core %.2d - The Result Was : %s\n",rank,temp);
				printf("Done! You can ignore error message below.\n\n");
				free(hash);
				Q_CALL(MPI_Abort(MPI_COMM_WORLD,MPI_SUCCESS)); //keep using mpi abort until find better solution
			}
		}
	}

	MPI_Finalize();
	return 0;
}
