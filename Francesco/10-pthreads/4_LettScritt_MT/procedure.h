#include <pthread.h>

#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef long msg;

typedef struct{
	pthread_mutex_t mutex;
	pthread_cond_t ok_lett_cv;
	pthread_cond_t ok_scritt_cv;

	int numlettori;
	int numscrittori;
	int num_lettori_wait;
	int num_scrittori_wait;
	msg mess;
} LettScritt;

void* Lettore(void*);
void* Scrittore(void*);

void Scrivi(LettScritt*, msg);
msg Leggi(LettScritt*);

void InizioLettura(LettScritt*);
void FineLettura(LettScritt*);
void InizioScrittura(LettScritt*);
void FineScrittura(LettScritt*);

#endif //PROCEDURE_H
