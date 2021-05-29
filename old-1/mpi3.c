#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "openssl/md5.h"

//complie with
//mpicc mpi3.c -o mpi3 -lcrypto
//this test program uses md5 library from openssl
//https://github.com/openssl/openssl/tree/master/include/openssl

//thanks to
//https://stackoverflow.com/questions/7627723/how-to-create-a-md5-hash-of-a-string-in-c
char *strMD5(const char *str, int length) {
	int n;
	MD5_CTX c;
	unsigned char digest[16];
	char *out=(char*)malloc(33);
	MD5_Init(&c);
	while(length>0) {
		if(length>512) {
			MD5_Update(&c, str, 512);
		}else{
			MD5_Update(&c, str, length);
		}
		length -= 512;
		str += 512;
	}
	MD5_Final(digest, &c);
	for (n=0; n<16; ++n) {
		snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
	}
	return out;
}

int main(int argc, char **argv){
//some variables
	int rank;
	int processor=4; //amount of cores
	int i,j,k,mark=0; ///loop variable
	char *temp=malloc(sizeof(char)*33); //temporary
	char dict[62]="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char data[]="21c2e59531c8710156d34a3c30ac81d5";

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

//mpi algorithm begin
	//line below for slave node
	for(i=0;i<processor;i++){
		//line below for master node
		if(i==0 && rank==0){
               	 	printf("Core=%.2d\n",rank);
               	 	for(j=i;j<62;j+=processor){
				temp=strMD5(&dict[j],1);
				//printf("%c %s\n",dict[j],temp); //debug_line_can_be_removed
				for(k=0;k<33;k++){
					if(temp[k]==data[k]){
						mark++;
					}else if(temp[k]!=data[k]){
                                                break;
                                        }

				}
				if(mark==33){
					printf("Core %.2d - The Result Was : %c\n",rank,dict[j]);
					free(temp);
					MPI_Finalize();
				}else{
					mark=0;
				}
			}
	        }
		//line below for slave node
		if(i>=1 && rank==i){
			printf("Core=%.2d\n",rank);
                        for(j=i;j<62;j+=processor){
                                temp=strMD5(&dict[j],1);
                                //printf("%c %s\n",dict[j],temp); //debug_line_can_be_removed
                                for(k=0;k<33;k++){
                                        if(temp[k]==data[k]){
                                                mark++;
                                        }else if(temp[k]!=data[k]){
                                                break;
                                        }

                                }
                                if(mark==33){
                                        printf("Core %.2d - The Result Was : %c\n",rank,dict[j]);
                                        free(temp);
                                        MPI_Finalize();
                                }else{
                                        mark=0;
                                }
                        }

		}
	}

//MPI finalize
	MPI_Finalize();
	return 0;
}
