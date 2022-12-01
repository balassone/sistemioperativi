#include <stdio.h>
#include "procedure.h"

void init_monitor(MonitorProdCons* p){
	pthread_mutex_init(&p->mutex,NULL);
	pthread_cond_init(&p->cv_cons,NULL);
	pthread_cond_init(&p->cv_prod,NULL);
	pthread_cond_init(&p->cv_consumazioni,NULL);
	p->testa=0;
	p->coda=0;
	for(int i=0; i<DIM; i++){
		p->buffer[i]=0;
	}
	p->conteggio_elementi=0;
	p->conteggio_consumazioni=0;
}

void produzione(MonitorProdCons* p, int val){
	pthread_mutex_lock(&p->mutex);
	while(p->conteggio_elementi==DIM){
		pthread_cond_wait(&p->cv_prod,&p->mutex);
	}
	
	p->buffer[p->testa] = val;
	p->testa=(p->testa+1) % DIM;
	p->conteggio_elementi++;
	pthread_cond_signal(&p->cv_cons);
	pthread_mutex_unlock(&p->mutex);
}

int consumazione(MonitorProdCons* p){
	pthread_mutex_lock(&p->mutex);

	while(p->conteggio_elementi==0) pthread_cond_wait(&p->cv_cons,&p->mutex);
	int val=p->buffer[p->coda];
	p->coda=(p->coda+1)%DIM;
	p->conteggio_elementi--;
	p->conteggio_consumazioni++;
	pthread_cond_signal(&p->cv_consumazioni); //Attende il verificarsi di condizioni
	pthread_cond_signal(&p->cv_prod);
	pthread_mutex_unlock(&p->mutex);
	return val;
}

int attendi_consumazioni(MonitorProdCons* p, int soglia){
	pthread_mutex_lock(&p->mutex);
	int n;
	while(p->conteggio_consumazioni<soglia){
		pthread_cond_wait(&p->cv_consumazioni,&p->mutex);
	}
	n=p->conteggio_consumazioni;
	p->conteggio_consumazioni=0;
	pthread_mutex_unlock(&p->mutex);
	return n;
}

void remove_monitor(MonitorProdCons* p){
	pthread_mutex_destroy(&p->mutex);
	pthread_cond_destroy(&p->cv_cons);
	pthread_cond_destroy(&p->cv_prod);
	pthread_cond_destroy(&p->cv_consumazioni);
}
