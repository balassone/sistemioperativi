#ifndef HEADER_H
#define HEADER_H

#include <pthread.h>

typedef struct{

	int buffer;

	int numlettori;
	int numscrittori;
	int lettori_wait;
	int scrittori_wait;
	pthread_mutex_t mutex;
	pthread_cond_t cv_lett;
	pthread_cond_t cv_scritt;
} LettScritt;

void inizioLettura(LettScritt*);
void fineLettura(LettScritt*);
void inizioScrittura(LettScritt*);
void fineScrittura(LettScritt*);

void Scrivi(LettScritt*, int);
int Leggi(LettScritt*);

void* Lettore(void*);
void* Scrittore(void*);

#endif
