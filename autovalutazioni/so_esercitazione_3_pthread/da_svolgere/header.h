#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>



struct monitor {

	int molo;
	int id_nave;

	/* TODO: Aggiungere variabili per la sincronizzazione */
	int numlettori;
	int numscrittori;
	int lettori_wait;
	int scrittori_wait;

	pthread_mutex_t mutex;
	pthread_cond_t cv_lett;
	pthread_cond_t cv_scritt;
};

void inizializza(struct monitor * m);
void rimuovi (struct monitor * m);
void scrivi_molo(struct monitor * m, int molo);
int leggi_molo(struct monitor * m);



#endif
