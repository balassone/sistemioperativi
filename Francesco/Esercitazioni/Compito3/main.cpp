#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include "header.h"

#define NPROD 3 
#define NCONS 3
int main(){
	pthread_t produttori[NPROD];
	pthread_t consumatori[NCONS];
	pthread_t contatore;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

	ProdCons* pc = (ProdCons*) malloc(sizeof(ProdCons));

	for(int i=0; i<DIM; ++i) pc->buffer[i]=0;
	pc->testa=0;
	pc->coda=0;
	pc->conteggio_consumazioni=0;
	pthread_mutex_init(&(pc->mutex),NULL);
	pthread_cond_init(&(pc->ok_prod),NULL);
	pthread_cond_init(&(pc->ok_cons),NULL);
	pthread_cond_init(&(pc->consumazioni),NULL);


	for(int i=0; i<NCONS; ++i){
		pthread_create(&consumatori[i],&attr,Consumatore,(void*)pc);
	}

	for(int i=0; i<NPROD; ++i){
		pthread_create(&produttori[i],&attr,Produttore,(void*) pc);
	}

	pthread_create(&contatore,&attr,Contatore,(void*)pc);

	for(int i=0; i<NCONS; ++i) pthread_join(consumatori[i],NULL);
	for(int i=0; i<NPROD; ++i) pthread_join(produttori[i],NULL);
	pthread_join(contatore,NULL);



	pthread_cond_destroy(&(pc->consumazioni));
	pthread_cond_destroy(&(pc->ok_cons));
	pthread_cond_destroy(&(pc->ok_prod));
	pthread_mutex_destroy(&(pc->mutex));
	free(pc);
	pthread_attr_destroy(&attr);
	pthread_exit(0);
}
