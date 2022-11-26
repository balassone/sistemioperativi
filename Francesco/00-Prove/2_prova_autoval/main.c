#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <time.h>

#include "procedure.h"

int main() {

	int id_queue, id_shm;
	key_t chiave_shm = IPC_PRIVATE; // DONE definire chiavi;
	key_t chiave_mbx = IPC_PRIVATE; //

	id_shm = shmget(chiave_shm,sizeof(struct MonitorRisultati),IPC_CREAT|0664);// DONE OTTENERE RISORSE
	id_queue = msgget(chiave_mbx,IPC_CREAT|0664); //

	if( id_shm < 0 || id_queue < 0) {
		perror("errore creazione risorse");
		exit(1);
	}

	struct MonitorRisultati * ls = (struct MonitorRisultati*) shmat(id_shm,NULL,0);//DONE ottenere riferimento al monitor

	init_monitor( &(ls->m), 2 );

	// DONE inizializzare risorse

	ls->numlettori=0;
	ls->numscrittori=0;

	for(int i=0; i<3; ++i) ls->risultati[i]=0;

	pid_t pid;

	int j;
	for(j=0; j < N_PRINTERS ; j++) {
		// DONE creare processi printer
		pid=fork();

		if(pid==0){
			printer(ls);
			exit(0);
		}
	
	}
	
	for(j=0; j < N_CALCOLATORI ; j++) {
		// DONE creare processi calcolatori
		pid=fork();

		if(pid==0){
			calcolo(ls,j+1,id_queue);
			exit(0);
		}
	}

	for(j=0; j < N_GENERATORI ; j++) {
		// DONE creare processi generatori
		
		pid=fork();

		if(pid==0){
			generazione(j+1,id_queue);
			exit(0);
		}

	}





	for(j=0; j<N_CALCOLATORI+N_GENERATORI+N_PRINTERS; j++)
		// DONE JOIN
		wait(NULL);

	// DONE REMOVE RESOUCES
	msgctl(id_queue,IPC_RMID,0);
	remove_monitor(&(ls->m));
	shmctl(id_shm,IPC_RMID,0);
	return 0;
}





