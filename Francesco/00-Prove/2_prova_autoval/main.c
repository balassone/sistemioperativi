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
	key_t chiave_shm = // TODO definire chiavi;
	key_t chiave_mbx = //

	id_shm = // TODO OTTENERE RISORSE
	id_queue = //

	if( id_shm < 0 || id_queue < 0) {
		perror("errore creazione risorse");
		exit(1);
	}

	struct MonitorRisultati * ls = //TODO ottenere riferimento al monitor

	init_monitor( &(ls->m), 2 );

	// TODO inizializzare risorse

	pid_t pid;

	int j;
	for(j=0; j < N_PRINTERS ; j++) {
		// TODO creare processi printer
	}
	
	for(j=0; j < N_CALCOLATORI ; j++) {
		// TDO creare processi calcolatori
	}

	for(j=0; j < N_GENERATORI ; j++) {
		// TODO creare processi generatori
	}





	for(j=0; j<N_CALCOLATORI+N_GENERATORI+N_PRINTERS; j++)
		// TODO JOIN

	// TODO REMOVE RESOUCES
}





