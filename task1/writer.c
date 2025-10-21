#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include "setting.h"

int shmWrite();

int main()
{
    int shmId;
    int* shmData; //s = 10 

    const char* path = PATH; 
    int id = ID;

    key_t key = ftok(path, id);

    //printf("%x\n", key);
    shmWrite(shmId, shmData, key);
    printf("\n-------[END WRITE]------\n");
    
    return 0;
}

int shmWrite(int shmId, int* shmData, key_t key)
{
    shmId = shmget(key, MSIZE, IPC_CREAT | 0666);
    if (shmId < 0)
    {
        perror("GET");
        exit(1);
    }

    shmData = (int*)shmat(shmId, NULL, 0);
    if (shmData == (int* )(-1))
    {
        perror("AT");
        exit(1);
    }
    
    for (int _i = 0; _i < 1000; _i++)
    {
        printf("Запись - %d\n", _i);
        shmData[_i] = _i + 1;
        if ((_i + 1) % 10 == 0) printf("\n");
    }

    printf("\n--------[DETACHING]--------\n");

    if (!shmdt(shmData))
    {
        perror("DT");
        exit(1);
    }
    

    
    return 0;

}

