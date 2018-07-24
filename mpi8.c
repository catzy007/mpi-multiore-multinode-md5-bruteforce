#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "openssl/md5.h"

//compile with mpicc cmpi.c -o cmpi -lcrypto
//this test program uses md5 library from openssl
//https://github.com/openssl/openssl/tree/master/include/openssl

//string to md5 function
//thanks to
//https://stackoverflow.com/questions/7627723/how-to-create-a-md5-hash-of-a-string-in-c
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

int main(int argc, char **argv){
//some variables
	int rank;
	int processor; //amount of cores
	int i,j,mark=0; ///loop variable
	int s1,s2,s3,s4,s5,s6,s7,s8,step=8; //loop variables for key generator
	char temp[9]={'\0'}; //temporary variables for generated key (n+1)
	char *out=malloc(sizeof(char)*33); //temporary0 md5 hash
	char *hash; //temporary1 md5 hash
	char dict[62]="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; //dictionary

	char data[]="a812eab6c966fd94bf9ed495f1d172c1"; //testcase

//initializing MPI
	MPI_Init(&argc, &argv);
	MPI_Request isreq, irreq;
	MPI_Comm_size(MPI_COMM_WORLD, &processor); //get the core count
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //get the core rank

	//line below for master node
	if(rank==0){
		printf("MPI MD5 BREAKER\nCore : %d\nData : %s\n",processor,data);
	}

//mpi algorithm begin
	for(i=0;i<processor;i++){
		if(rank==i){
			printf("Hello From Core %.2d\n",rank);
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
			for(s3=0;s3<62;s3++){
			for(s2=0;s2<62;s2++){
			for(s1=i;s1<62;s1+=processor){
				temp[0]=dict[s8];
				temp[1]=dict[s7];
				temp[2]=dict[s6];
				temp[3]=dict[s5];
				temp[4]=dict[s4];
				temp[5]=dict[s3];
				temp[6]=dict[s2];
				temp[7]=dict[s1];
				hash=strMD5(temp,step,out);
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
			}//s1
			}//s2
			}//s3
			}//s4
			}//s5
			}//s6
			}//s7
			}//s8
			if(s8<62){
				finalize0:
				printf("Core %.2d - The Result Was : %s\n",rank,temp);
				free(hash);
				MPI_Abort(MPI_COMM_WORLD,MPI_SUCCESS);
			}
		}
	}

	MPI_Finalize();
	return 0;
}
