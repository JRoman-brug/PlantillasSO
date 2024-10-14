#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <errno.h>
#include <pthread.h>

#define MEM_SIZE sizeof(data_t)
#define CANT 10
typedef struct {
    sem_t vacio;
    sem_t lleno;
} data_t;


int main(){
    key_t key = ftok("/key", 64);
    int id = shmget(key, MEM_SIZE, IPC_CREAT | 0666);
    data_t *data = (struct data_t *) shmat(id,0,0);

    
    sem_init(&(data->vacio), 1, CANT);
    sem_init(&(data->lleno), 1, 0);

    sem_destroy(&(data->vacio));
    sem_destroy(&(data->lleno));

    shmdt(data);
    shmctl(id, IPC_RMID, NULL);
}