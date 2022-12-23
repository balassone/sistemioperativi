#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#include "header.h"

#define NUM_MESSAGGI_DA_RICEVERE 10

void * worker(void *);

typedef struct {

    int valore;
    BufferMutuaEsclusione * buffer;

} parametri_worker;

int main() {
	
	key_t key=ftok(FTOK_PATH_Q,FTOK_CHAR_Q);

    int id_coda = msgget(key,IPC_CREAT|0664);/* TBD: Accedere alla coda di messaggi allocata dal processo padre */



    BufferMutuaEsclusione * buffer = (BufferMutuaEsclusione*) malloc(sizeof(BufferMutuaEsclusione));/* TBD: Allocare la struttura dati da condividere con i thread worker */

    buffer->valore = 0;
    
	/* TBD: Completare l'inizializzazione di "buffer" */
	pthread_mutex_init(&(buffer->mutex),NULL);

    /* Il programma avvierà un thread worker distinto 
     * per ogni messaggio ricevuto
     */
    pthread_t thread_worker[NUM_MESSAGGI_DA_RICEVERE];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

	parametri_worker* params = (parametri_worker*) malloc(sizeof(parametri_worker));
	params->buffer=buffer;
    params->valore=0;
	Messaggio m;
	for(int i=0; i<NUM_MESSAGGI_DA_RICEVERE; i++) {

        /* TBD: Effettuare la ricezione del messaggio */
		msgrcv(id_coda,&m,sizeof(Messaggio)-sizeof(long),MESSAGGIO,0);
		params->valore=m.msg;	
        printf("[SERVER] Ricezione: %d\n", m.msg);

        /* TBD: Creare un thread figlio, facendogli eseguire la
         *      funzione "worker", e passandogli sia il valore ricevuto
         *      sia il "buffer", tramite la struttura dati "parametri_worker"
         */       
		 pthread_create(&thread_worker[i],&attr,worker,(void*)params);
    }


    /* TBD: Attendere la terminazione dei thread figli */
	for(int i=0; i<NUM_MESSAGGI_DA_RICEVERE; i++) pthread_join(thread_worker[i],NULL);

    /* TBD: De-allocazione della struttura dati "buffer" */

	pthread_mutex_destroy(&(buffer->mutex));
	pthread_attr_destroy(&attr);
	free(buffer);
	free(params);

    return 0;

}


void * worker(void * p) {
	parametri_worker* params=(parametri_worker*) p;
    BufferMutuaEsclusione * buffer = params->buffer;/* TBD: Completare il passaggio dei parametri */;
    int valore = params->valore;/* TBD: Completare il passaggio dei parametri */;


    /* TBD: Effettuare la modifica del buffer in mutua esclusione */
	pthread_mutex_lock(&(buffer->mutex));
    sleep(1);

    buffer->valore += valore;

    printf("[WORKER] Nuovo valore del buffer: %d\n", buffer->valore);

	pthread_mutex_unlock(&(buffer->mutex));
    return NULL;
}
