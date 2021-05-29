#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int function(int arr[], int min, int max){
	int x,temporary=0;
	for(x=min;x<max;x++){
		temporary+=arr[x];
	}
	return temporary;
}

int main(int *argc, char **argv){

	int rank;
	int processor=4; //amount of cores
	int data[8]={1,2,3,4,5,6,7,8}; //data to process
	int result[2]={0,0}; //this is a container
	int i,j,temp=0; //loop variable and temporary

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	//for(i=0;i<processor;i++){
	//	if
	//}

	if(rank==1){
		temp=function(data,4,8);
		printf("this is processor %d\n",rank);
		system("hostname");
		MPI_Send(&temp,1,MPI_INT,0,1033,MPI_COMM_WORLD);
	}else if(rank==0){
		result[0]=function(data,0,4);
		printf("this is processor %d\n",rank);
		system("hostname");
		MPI_Recv(&result[1],1,MPI_INT,1,1033,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("%d %d\n",result[0],result[1]);
	}

	MPI_Finalize();
	return 0;
}
