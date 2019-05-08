#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int function(int arr[], int min, int max){
	int x,temporary=0;
	for(x=min;x<max+1;x++){
		temporary+=arr[x];
	}
	return temporary;
}

<<<<<<< HEAD
int main(int argc, char **argv){
=======
int main(int *argc, char **argv){
>>>>>>> 68146fe94c1355888b641769eefac8ffbe999d6c
//some variables
	int rank;
	int processor=4; //amount of cores
	int data[8]={1,1,2,2,3,3,4,4}; //data to process
	int result[4]={0,0,0,0}; //this is a container
	int i,j,temp=0; //loop variable and temporary

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

//mpi algorithm begin
	//line below for slave node
	for(i=0;i<processor;i++){
		//line below for master node
		if(i==0 && rank==0){
                	result[0]=function(data,i*2,i*2+1);
               	 	printf("Core=%.2d - i=%.2d - i1=%.2d i2=%.2d - Result=%.2d\n",rank,i,i*2,i*2+1,result[i]);
               	 	for(i=1;i<processor;i++){
                        	MPI_Recv(&result[i],1,MPI_INT,MPI_ANY_SOURCE,i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                	}
       	        	printf("\n%d %d %d %d\n",result[0],result[1],result[2],result[3]);
	        }
		//line below for slave node
		if(i>=1 && rank==i){
			result[i]=function(data,i*2,i*2+1);
                        printf("Core=%.2d - i=%.2d - i1=%.2d i2=%.2d - Result=%.2d\n",rank,i,i*2,i*2+1,result[i]);
			MPI_Send(&result[i],1,MPI_INT,0,i,MPI_COMM_WORLD);
		}
	}

//MPI finalize
	MPI_Finalize();
	return 0;
}
