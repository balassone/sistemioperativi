#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "header.h"

void inizializza_vettore(VettoreProdCons * p) {

    /* TBD: Inizializzare la struttura dati "VettoreProdCons" */
	init_monitor(&(p->m),2);
	for(int i=0; i<DIM; ++i){
		p->buffer[i]=0;
	}
	p->testa=0;
	p->coda=0;
}

void produci(VettoreProdCons * p, int valore) {

    /* TBD: Implementare la sincronizzazione, mediante
     *      l'algoritmo del vettore circolare di buffer
     */
	enter_monitor(&(p->m));
	if((p->testa + 1)%DIM==p->coda){
		wait_condition(&(p->m),CV_PROD);
	}
	p->buffer[p->testa]=valore;
	p->testa=(p->testa+1)%DIM;
	signal_condition(&(p->m),CV_CONS);
	leave_monitor(&(p->m));
}

int consuma(VettoreProdCons * p) {

    int valore;

    /* TBD: Implementare la sincronizzazione, mediante
     *      l'algoritmo del vettore circolare di buffer
     */
	 enter_monitor(&(p->m));
	 if(p->testa==p->coda) wait_condition(&(p->m),CV_CONS);
	 valore=p->buffer[p->coda];
	 p->coda=(p->coda+1)%DIM;
	 signal_condition(&(p->m),CV_PROD);
	 leave_monitor(&(p->m));
	 return valore;

}

void rimuovi_vettore(VettoreProdCons * p) {
	remove_monitor(&(p->m));
}


void inizializza_buffer(BufferMutuaEsclusione * p) {

    /* TBD: Inizializzare la struttura dati "BufferMutuaEsclusione" */
	p->sem_id=semget(IPC_PRIVATE,1,IPC_CREAT|0664);
	semctl(p->sem_id,MUTEX,SETVAL,1);
	p->buffer=0;
}

void aggiorna(BufferMutuaEsclusione * p, int valore) {

    /* TBD: Aggiungere la sincronizzazione per la mutua esclusione */
	Wait_Sem(p->sem_id,MUTEX);
    p->buffer += valore;

    printf("[AGGIORNA] Nuovo valore del buffer: %d\n", p->buffer);
	Signal_Sem(p->sem_id,MUTEX);
}

void rimuovi_buffer(BufferMutuaEsclusione * p) {

    /* TBD: De-inizializzare la struttura dati "BufferMutuaEsclusione" */
	semctl(p->sem_id,0,IPC_RMID);
}


