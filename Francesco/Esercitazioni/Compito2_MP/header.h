#ifndef _HEADER_
#define _HEADER_

#include "monitor_hoare.h"
#include "semafori.h"

#define DIM 3
#define MUTEX 0
#define CV_PROD 0
#define CV_CONS 1
typedef struct {

    int buffer[DIM];
	int testa;
	int coda;
	Monitor m;
} VettoreProdCons;

typedef struct {

    int buffer;

    int sem_id;  // Utilizzare questa variabile per la mutua esclusione

} BufferMutuaEsclusione;

void inizializza_vettore(VettoreProdCons * p);
void produci(VettoreProdCons * p, int valore);
int consuma(VettoreProdCons * p);
void rimuovi_vettore(VettoreProdCons * p);

void inizializza_buffer(BufferMutuaEsclusione * p);
void aggiorna(BufferMutuaEsclusione * p, int valore);
void rimuovi_buffer(BufferMutuaEsclusione * p);


#endif
