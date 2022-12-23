#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

typedef struct {
    int buffer[MAX_VALUES];
    // TODO aggiungere le variabili per la gestione circolare
    // e per la sincronizzazione dei thread
	
	int testa;
	int coda;

	pthread_mutex_t mutex;
	pthread_cond_t ok_prod;
	pthread_cond_t ok_cons;

} data_str;

typedef struct {
    int somma;
    int num_valori_sommati;
    // TODO aggiungere le variabili per la sincronizzazione dei thread
	pthread_cond_t cv_valori;
	pthread_mutex_t mutex;
} somma_valori;

// VARIABILI GLOBALI:
// la struttura
data_str shared_buf;
// le code
int queue_req;
int queue_res;

int consuma() {
    int value;
    //TODO consumatore, con gestione coda circolare
	pthread_mutex_lock(&(shared_buf.mutex));
	while(shared_buf.testa==shared_buf.coda){
		pthread_cond_wait(&(shared_buf.ok_cons),&(shared_buf.mutex));
	}

	value=shared_buf.buffer[shared_buf.coda];
	shared_buf.coda=(shared_buf.coda+1)%MAX_VALUES;
	pthread_cond_signal(&(shared_buf.ok_prod));
	pthread_mutex_unlock(&(shared_buf.mutex));
    return value;
}

void produci(int new_value) {
    //TODO produttore, con gestione coda circolare

	pthread_mutex_lock(&(shared_buf.mutex));

	while((shared_buf.testa+1)%MAX_VALUES==shared_buf.coda){
		pthread_cond_wait(&(shared_buf.ok_prod),&(shared_buf.mutex));
	}

	shared_buf.buffer[shared_buf.testa]=new_value;
	shared_buf.testa=(shared_buf.testa+1)%MAX_VALUES;
	pthread_cond_signal(&(shared_buf.ok_cons));
	pthread_mutex_unlock(&(shared_buf.mutex));

}


void * stampa_somma(void* par) {
    
    somma_valori * s = (somma_valori*) par/*TODO: recupero parametro*/;
    
    //TODO attesa che siano stati sommati NUM_CONS valori utilizzando una condition
    // e stampa della somma una volta verificata la condizione

	while(s->num_valori_sommati<NUM_CONS){
		pthread_cond_wait(&(s->cv_valori),&(s->mutex));
	}
	printf("Somma Valori: %d\n",s->somma);

    pthread_exit(NULL);
}

void * produttore(void* par) {
    // par qui non serve, può essere ignorato
    int new_value;
    int i;
    for (i = 0; i < NUM_UPDATES*MAX_VALUES; i++) {
        new_value = rand()%10+1;
        printf("PRODUTTORE: inserimento nuovo dato: %d\n",new_value);
        produci(new_value);
        sleep(rand()%3+1);
    }
    pthread_exit(NULL);
}


void * consumatore(void* par) {
    somma_valori * s = (somma_valori*) par/*TODO: recupero parametro*/;
    int i;
    for (i = 0; i < NUM_CONS; i++) {
        req msg;
        //TODO ricezione messaggio di richiesta
		msgrcv(queue_req,(void*)&msg,sizeof(req)-sizeof(long),0,0);
        printf("CONSUMATORE_SERV: ricevuta richiesta di consumo\n");

        res risp;
        //TODO preparazione messaggio di risposta, usando funzione "consuma"
		risp.value=consuma();
		risp.type=1;
        printf("CONSUMATORE_SERV: invio valore al consumatore client %d\n",risp.value);
        //TODO invio risposta
        msgsnd(queue_res,(void*)&risp,sizeof(risp)-sizeof(long),0);
        //TODO aggiornamento della somma in 's' con il nuovo valore appena consumato
        //TODO e notifica della condizione quando sommati NUM_CONS elementi
		s->somma=s->somma+risp.value;
		s->num_valori_sommati=s->num_valori_sommati+1;
		if(s->num_valori_sommati==NUM_CONS) pthread_cond_signal(&(s->cv_valori));
    }

    pthread_exit(NULL);
}

int main() {

    //TODO: completare l'inizializzazione code
    key_t msg_req_key = ftok(".",'q');/*..*/
	key_t msg_res_key = ftok(".",'s');/*..*/

    queue_req = msgget(msg_req_key,IPC_CREAT|0664);/*..*/
	queue_res = msgget(msg_res_key,IPC_CREAT|0664);/*..*/

    //TODO inizializzazione di "shared_buf"

	for(int i=0; i<MAX_VALUES; ++i){
		shared_buf.buffer[i]=0;
	}
	
	shared_buf.testa=0;
	shared_buf.coda=0;
	pthread_mutex_init(&(shared_buf.mutex),NULL);
	pthread_cond_init(&(shared_buf.ok_prod),NULL);
	pthread_cond_init(&(shared_buf.ok_cons),NULL);

    pthread_t prod, cons, sum;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    srand(time(NULL));

    somma_valori* s = (somma_valori*) malloc(sizeof(somma_valori));/*TODO allocazione struttura*/;
    // TODO e inizializzazione valori
	
    s->somma=0;
	s->num_valori_sommati=0;
	pthread_mutex_init(&(s->mutex),NULL);
	pthread_cond_init(&(s->cv_valori),NULL);
    

	//TODO creazione dei tre thread prod cons e sum
    // nota: ai thread cons e sum bisogna passare la struttura s
	pthread_create(&prod,&attr,produttore,NULL);
	pthread_create(&cons,&attr,consumatore,(void*) s);
	pthread_create(&sum,&attr,stampa_somma,(void*) s);
    //TODO join 
	pthread_join(prod, NULL);
	pthread_join(cons,NULL);
	pthread_join(sum,NULL);
    //TODO rimozione code e struttura s
	
	pthread_mutex_destroy(&(shared_buf.mutex));
	pthread_cond_destroy(&(shared_buf.ok_prod));
	pthread_cond_destroy(&(shared_buf.ok_cons));
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&(s->mutex));
	pthread_cond_destroy(&(s->cv_valori));
	free(s);
	msgctl(queue_req,IPC_RMID,NULL);
	msgctl(queue_res,IPC_RMID,NULL);
    
	return 0;
}
