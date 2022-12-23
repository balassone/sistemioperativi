#ifndef HEADER_H
#define HEADER_H

#include <pthread.h>
#define DIM 5
#define SOGLIA 5
#define PRODUZIONI 10
#define CONSUMAZIONI 10
typedef struct{
	
	int buffer[DIM]; //Inizializza zeri
	int testa; //0
	int coda; //0
	int conteggio_consumazioni; //0

	pthread_cond_t consumazioni;
	pthread_cond_t ok_prod;
	pthread_cond_t ok_cons;
	pthread_mutex_t mutex;
} ProdCons;

void Produci(ProdCons*,int);
int Consuma(ProdCons*);
int attendi_consumazioni(ProdCons*, int);

void* Produttore(void*);
void* Consumatore(void*);
void* Contatore(void*);

#endif
