#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include "setting.h"

int shmRead();

int main()
{
    int shmId;
    int* shmData;

    const char* path = PATH;
    int id = ID;

    key_t key = ftok(path, id);

    //printf("%x\n", key);
    shmRead(shmId, shmData, key);
    return 0;
}

int shmRead(int shmId, int* shmData, key_t key)
{

    shmId = shmget(key, MSIZE, 0666);
    if (shmId < 0)
    {
        perror("GET");
        exit(1);
    }

    shmData = (int*)shmat(shmId, NULL, 0);
    if (shmData == (void* )(-1))
    {
        perror("AT");
        exit(1);
    }

    for (int _i = 0; _i < 1000; _i++)
    {
        printf("Чтение - %d\n", shmData[_i]);
        if ((_i + 1) % 10 == 0) printf("\n");
    }

    shmdt(shmData);
    shmctl(shmId, IPC_RMID, NULL);

    return 0;

}
