#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>

key_t key;
int msgid;

typedef struct {
    long type;
    int product;
} mensaje_t;

size_t msgSize = (sizeof(mensaje_t)-sizeof(long));

int main(){
    key = ftok("msgRoman",64);//Tiro mensajes a las wachas
    //Creo o vinculo la cola de mensajes
    msgid = msgget(key, 0660 | IPC_CREAT);
    
    mensaje_t msg;
    msg.type = 1;
    msg.product = 0;
    msgsnd(msgid, &msg, msgSize, 0);
    

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}