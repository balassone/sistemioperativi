#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include "header.h"

#define NUM_CLIENT 2

int main() {

	key_t key=ftok(FTOK_PATH_Q,FTOK_CHAR_Q);
    int id_coda = msgget(key,IPC_CREAT|0664);/* TBD: Allocare una coda di messaggi */

	if(id_coda<0) perror("ERRORE CODA");

    for(int i=0; i<NUM_CLIENT; i++) {

        /* TBD: Creare i processi figli "client", e
         *      fargli eseguire il programma "main_client"
         */
		 int pid=fork();
		 if(pid==0){
			execl("./main_client","./main_client",NULL);
		 	printf("Problema execl!");
		 }
    }


    /* TBD: Creare i processi figli "client", e
     *      fargli eseguire il programma "main_client"
     */

	int pid=fork();
	if(pid==0) execl("./main_server","./main_server",NULL);
    /* TBD: Attendere la terminazione dei processi figli */

	for(int i=0; i<NUM_CLIENT+1; ++i) wait(NULL);

    /* TBD: De-allocare la coda di messaggi */
	msgctl(id_coda,IPC_RMID,NULL);

    return 0;

}
