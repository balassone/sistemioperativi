#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#include "header.h"

#define NUM_MESSAGGI_DA_INVIARE 5

int main() {
	key_t key = ftok(FTOK_PATH_Q, FTOK_CHAR_Q);
    int id_coda = msgget(key,IPC_CREAT|0664); /* TBD: Accedere alla coda di messaggi allocata dal processo padre */


    srand(getpid());
    
    for(int i=0; i<NUM_MESSAGGI_DA_INVIARE; i++) {

        int valore = rand() % 10;

        printf("[CLIENT] Invio: %d\n", valore);

        /* TBD: Inviare il valore tramite un messaggio */
		Messaggio m;
		m.type=MESSAGGIO;
		m.msg=valore;
		msgsnd(id_coda,(void*)&m,sizeof(Messaggio)-sizeof(long),0);
	}

    return 0;

}
