#include "header.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
void Produci(ProdCons* pc, int val){
	pthread_mutex_lock(&(pc->mutex));
	while((pc->testa+1)%DIM==pc->coda){
		pthread_cond_wait(&(pc->ok_prod),&(pc->mutex));
	}
	sleep(1);
	pc->buffer[pc->testa]=val;
	pc->testa=(pc->testa+1)%DIM;
	pthread_cond_signal(&(pc->ok_cons));
	pthread_mutex_unlock(&(pc->mutex));
}

int Consuma(ProdCons* pc){
	pthread_mutex_lock(&(pc->mutex));
	while(pc->testa==pc->coda){
		pthread_cond_wait(&(pc->ok_cons),&(pc->mutex));
	}
	int val=pc->buffer[pc->coda];
	pc->coda=(pc->coda+1)%DIM;
	pc->conteggio_consumazioni=pc->conteggio_consumazioni+1;
	if(pc->conteggio_consumazioni==SOGLIA) pthread_cond_signal(&(pc->consumazioni));
	pthread_cond_signal(&(pc->ok_prod));
	pthread_mutex_unlock(&(pc->mutex));
	return val;
}

int attendi_consumazioni(ProdCons* pc, int soglia){
	pthread_mutex_lock(&(pc->mutex));
	while(pc->conteggio_consumazioni<soglia){
		pthread_cond_wait(&(pc->consumazioni),&(pc->mutex));
	}
	int val=pc->conteggio_consumazioni;
	printf("SOGLIA COLPITA A %d CONSUMAZIONI\n",val);
	pc->conteggio_consumazioni=0;
	pthread_mutex_unlock(&(pc->mutex));
	return val;
}

void* Produttore(void* p){
	ProdCons* pc = (ProdCons*) p;
	int myd=gettid();
	srand(myd);
	for(int i=0; i<PRODUZIONI; ++i){
		int val=rand()%100;
		printf("[%d] Produco il valore %d\n",myd,val);
		Produci(pc,val);
	}
	pthread_exit(0);
}

void* Consumatore(void* p){
	ProdCons* pc = (ProdCons*) p;
	int myd=gettid();
	for(int i=0; i<CONSUMAZIONI; ++i){
		int val=Consuma(pc);
		printf("[%d] Consumo il valore %d\n",myd,val);
	}
	pthread_exit(0);
}

void* Contatore(void* p){
	ProdCons* pc = (ProdCons*) p;
	int myd=gettid();
	int val=0;
	while(val<30){
		val += attendi_consumazioni(pc,SOGLIA);
		printf("[%d] Conteggio totale: %d\n",myd, val);
	}
	pthread_exit(0);
} 
