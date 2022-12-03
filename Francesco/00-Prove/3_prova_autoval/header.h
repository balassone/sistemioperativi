#ifndef _HEADER_
#define _HEADER_

#include <pthread.h>

#define DIM 3

#define NUM_CONS 5

#define LIBERO 0
#define INUSO 1
#define OCCUPATO 2

typedef struct {

    int buffer[DIM];

    int stato[DIM];

    // DONE: completare campi della struttura per la gestione in mutua esclusione del pool di buffer
	int liberi; 
	int occupati; 
	
	pthread_mutex_t mutex;
	pthread_cond_t cv_prod;
	pthread_cond_t cv_cons;

} VettoreProdCons;

typedef struct {

    int buffer;
    int num_somme;

     // DONE: completare campi della struttura per la gestione in mutua esclusione del buffer
	
	pthread_mutex_t mutex;
	pthread_cond_t cv_visual;
	pthread_cond_t cv_cons;

} BufferMutuaEsclusione;

void inizializza_vettore(VettoreProdCons * p);
void produci(VettoreProdCons * p, int valore);
int consuma(VettoreProdCons * p);
void rimuovi_vettore(VettoreProdCons * p);

void inizializza_buffer(BufferMutuaEsclusione * p);
void aggiorna_buffer(BufferMutuaEsclusione * p, int valore);
void rimuovi_buffer(BufferMutuaEsclusione * p);

int stampa_valore(BufferMutuaEsclusione * p);


#endif
