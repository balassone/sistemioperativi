#include "monitor_hoare.h"

#define CV_PROD 0
#define CV_CONS 1
#define DIM 3
#define MUTEX 0 //Sono implementati separatamente

#define NUM_PRODUTTORI 2
#define NUM_CONSUMATORI 5

#define NUM_PRODUZIONI 10

#define NUM_CONSUMI 4

typedef struct{
	
	int buffer[DIM];
	int testa;
	int coda;

	Monitor m;

} VettoreProdCons;

typedef struct {
	int valore;
	int semid;
} BufferMutuaEx;

void inizializza_vettore(VettoreProdCons* vett);
void rimuovi_vettore(VettoreProdCons* vett);
void inizializza_buffer(BufferMutuaEx* buff);
void rimuovi_buffer(BufferMutuaEx* buff);
void produci(VettoreProdCons* vett, int val);
int consuma(VettoreProdCons* vett);
void aggiorna_buffer(BufferMutuaEx* buff, int val);
