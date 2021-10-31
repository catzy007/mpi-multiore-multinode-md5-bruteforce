#include "bruteforce.h"
#include "md5parser.h"
#include "datetime.h"
#include <mpi.h>

void bruteforce(int length, int rank, int size, char *test){
    char out[33];
    char chrset[] = {"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    int chrsetLen=(sizeof(chrset)/sizeof(char))-1;

    char *progress;
    progress = malloc(sizeof(char)*length);
    int *idxProgress;
    idxProgress = malloc(sizeof(int)*length);

    //set initial state for index progress
    for(int i=0; i<=length; i++){
        progress[i] = '\0';
        idxProgress[i] = -1;
    }

    //bruteforce algorithm
    long loop=rank-1;
    while(1){
        // printf("%ld %d %d %d\n",loop,length,chrsetLen,idxProgress[length-1]);
        // for(int i=0; i<length; i++){
        //     printf("%d ",idxProgress[i]);
        // }
        indexToText(idxProgress, progress, chrset, length);
        if(compareResult(strMD5(progress,progressLen(progress,length),out), test, 33)){
            datetime();
            printf("Thread %.2d - The Result Was : %s\nDone!\n",rank,progress);
            free(progress); free(idxProgress);
            Q_CALL(MPI_Abort(MPI_COMM_WORLD,MPI_SUCCESS)); //keep using mpi abort until find better solution
            break;
        }

        for(int i=0; i<length; i++){
            if(i<3){
                idxProgress[0] = abs(loop)%chrsetLen;
                idxProgress[1] = abs(loop/chrsetLen)%chrsetLen;
                idxProgress[2] = abs(loop/chrsetLen/chrsetLen)%chrsetLen;
                if(loop > (chrsetLen*chrsetLen*chrsetLen)-1){
                    idxProgress[3] += 1;
                    loop = rank-1;
                }
            }
            if(idxProgress[i] > chrsetLen-1 && i>2){
                idxProgress[i+1] += 1;
                idxProgress[i] = 0;
            }
        }
        loop+=size;

        //printf("--%d %d\n",idxProgress[length-1],chrsetLen-1);
        if(idxProgress[length] >= 1){
            break;
        }
    }
    
    free(progress);
    free(idxProgress);
}

void indexToText(int *idxProgress, char *progress, char *chrset, int length){
    for(int i=0; i<length; i++){
        if(idxProgress[i] < 0){
            progress[i] = '\0';
        }else{
            progress[i] = chrset[idxProgress[i]];
        }
    }
}

int progressLen(char *progress, int maxlen){
    for(int i=0; i<maxlen; i++){
        if(progress[i] == '\0'){
            return i;
        }
    }
}

int compareResult(char *progress, char *test, int algorithmLen){
    for(int i=0; i<algorithmLen; i++){
        if(progress[i] != test[i]){
            return 0;
        }
    }
    return 1;
}