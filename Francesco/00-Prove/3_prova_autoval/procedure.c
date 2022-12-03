#include <stdio.h>
#include <unistd.h>

#include "header.h"

void inizializza_vettore(VettoreProdCons * p) {

	pthread_mutex_init(&(p->mutex),NULL);
	pthread_cond_init(&(p->cv_prod),NULL);
	pthread_cond_init(&(p->cv_cons),NULL);
	
	for(int i=0; i<DIM; ++i){
		p->buffer[i]=0;
		p->stato[i]=LIBERO;
	}
	
	p->liberi=DIM;
	p->occupati=0;

}

void produci(VettoreProdCons * p, int valore) {
	
	pthread_mutex_lock(&p->mutex); //Blocco sul mutex
	
	while(p->liberi==0){ //Signal and Continue
		
		pthread_cond_wait(&(p->cv_prod),&(p->mutex));
	
	}
	
	int i=0;
	while(i<DIM && p->stato[i]!=LIBERO){
	
		i++;
	
	}
	p->liberi=p->liberi-1;
	p->stato[i]=INUSO;
	
	pthread_mutex_unlock(&(p->mutex));

	sleep(2); // Operazione lenta
	p->buffer[i]=valore;

	pthread_mutex_lock(&(p->mutex));
	
	p->stato[i]=OCCUPATO;
	p->occupati=p->occupati+1;
	
	pthread_cond_signal(&(p->cv_cons));
	
	pthread_mutex_unlock(&(p->mutex));

}

int consuma(VettoreProdCons * p) {
	
	pthread_mutex_lock(&(p->mutex));

	while(p->occupati==0){
		pthread_cond_wait(&(p->cv_cons),&(p->mutex));
	}

	int i=0;
	while(i<DIM && p->stato[i]!=OCCUPATO){

		i++;

	}
	p->occupati=p->occupati-1;
	p->stato[i]=INUSO;
	
	pthread_mutex_unlock(&(p->mutex));

	int val = p->buffer[i];

	pthread_mutex_lock(&(p->mutex));
	
	p->stato[i]=LIBERO;
	p->liberi=p->liberi+1;
	
	pthread_cond_signal(&(p->cv_prod));
	pthread_mutex_unlock(&(p->mutex));
	return val;
}

void rimuovi_vettore(VettoreProdCons * p) {
	
	pthread_mutex_destroy(&(p->mutex));
	pthread_cond_destroy(&(p->cv_prod));
	pthread_cond_destroy(&(p->cv_cons));
	
}


void inizializza_buffer(BufferMutuaEsclusione * p) {
	
	p->buffer=0;
	p->num_somme=0;
	pthread_mutex_init(&(p->mutex),NULL);
	pthread_cond_init(&(p->cv_visual),NULL);
	pthread_cond_init(&(p->cv_cons),NULL);
}

void aggiorna_buffer(BufferMutuaEsclusione * p, int valore) {

    // DONE: incrementa il contenuto del buffer

	pthread_mutex_lock(&(p->mutex));

	while(p->num_somme==NUM_CONS){
		pthread_cond_wait(&(p->cv_cons),&(p->mutex));
	}

	p->num_somme=p->num_somme+1;

	p->buffer=p->buffer+valore;

	if(p->num_somme==NUM_CONS) pthread_cond_signal(&(p->cv_visual));
	
	pthread_mutex_unlock(&(p->mutex));
}

int stampa_valore(BufferMutuaEsclusione * p) {

    // DONE: Attendi il completamento di NUM_CONS consumazioni e stampa valore
	pthread_mutex_lock(&(p->mutex));
	
	while(p->num_somme<NUM_CONS){
		pthread_cond_wait(&(p->cv_visual),&(p->mutex));
	}
	
	int val=p->buffer;
	p->num_somme=0;
	
	pthread_cond_signal(&(p->cv_cons));
	pthread_mutex_unlock(&p->mutex);
	
	return val;
}

void rimuovi_buffer(BufferMutuaEsclusione * p) {
	
	pthread_mutex_destroy(&(p->mutex));
	pthread_cond_destroy(&(p->cv_visual));
	pthread_cond_destroy(&(p->cv_cons));

}
