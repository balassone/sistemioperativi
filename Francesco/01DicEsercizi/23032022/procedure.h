#ifndef PROCEDURE_H
#define PROCEDURE_H
#include <pthread.h>

#define DIM 5

typedef struct{
	int buffer[DIM];
	int testa;
	int coda;
	//Variabili per il while
	int conteggio_elementi;
	int conteggio_consumazioni; //Tenere traccia delle consumazioni

	pthread_mutex_t mutex;
	//Variabili su cui fare wait e signal
	pthread_cond_t cv_prod;
	pthread_cond_t cv_cons;
	pthread_cond_t cv_consumazioni;
} MonitorProdCons;

void init_monitor(MonitorProdCons* p);
void produzione(MonitorProdCons* p, int val);
int consumazione(MonitorProdCons* p);
int attendi_consumazioni(MonitorProdCons*, int soglia);
void remove_monitor(MonitorProdCons* p);

#endif
