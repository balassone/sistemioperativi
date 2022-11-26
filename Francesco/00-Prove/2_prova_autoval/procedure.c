#include "procedure.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <time.h>


float* leggi_risultati(struct MonitorRisultati * ls) {

	float* risultati = //TODO completare 


	printf("[%ld] Lettura - ingresso monitor\n", getpid());

	// TODO lettura

	printf("[%ld] Lettura - uscita monitor\n", getpid());

	return risultati;

}


void inserisci_risultato(struct MonitorRisultati * ls, float valore, int operazione) {

	// TODO scrittura
	
	printf("[%ld] Scrittura - ingresso monitor\n", getpid());

	printf("[%ld] Scrittura - valore [%f] operazione %d\n", getpid(),valore, operazione);

	printf("[%ld] Scrittura - uscita monitor\n", getpid());
}

void calcolo(struct MonitorRisultati * ls, int operazione, int mailbox){
	// TODO completa
}
void generazione(int operazione, int mailbox) {
	srand(time(NULL));
	// TODO completa
}
void printer(struct MonitorRisultati * ls) {
	float* risultati;
	for (int i = 0 ; i < 4; i++) {
		sleep(2);
		risultati = leggi_risultati(ls);
		printf("[%ld] Risultati 1: %f, 2: %f, 3: %f\n",getpid(), risultati[0], risultati[1], risultati[2]);
		//TODO COMPLETA DEALLOCAZIONE risultati
	}
}
