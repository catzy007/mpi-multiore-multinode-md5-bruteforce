#include <stdio.h>
#include <stdlib.h>
#include "md5parser.h"
#include "datetime.h"
#include "bruteforce.h"
#include <mpi.h>

void main(int argc, char **argv){
    char data[]="4c467321dd2d571a787706eb4466a09d";
    int rank,reply,size;

//initializing MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size); //get the core count
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //get the core rank

//line below for master node
	if(rank==0){
		printf("MPI MD5 BREAKER V2.0\n");
        printf("Size : %d\n",size);
		datetime();
		printf("Test : %s\n",data);
		printf("Hello From Thread %.2d\n",rank);
		//printf("%d %d\n",dictLen,dataLen); //debug_line_can_be_removed
		for(int i=1; i<size; i++){
			MPI_Recv(&reply,1,MPI_INT,i,1033,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("Hello From Thread %.2d\n",reply);
		}
	}
//preparing all thread
	for(int i=1; i<size; i++){
		if(rank==i){
			MPI_Send(&rank,1,MPI_INT,0,1033,MPI_COMM_WORLD);
		}
	}

//start bruteforce
    bruteforce(8,rank,size,data);
}
