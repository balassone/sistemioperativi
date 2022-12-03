#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "header.h"

#define NUM_PRODUTTORI 2
#define NUM_CONSUMATORI 20

#define PRODUZIONI 10

void * produttore(void *);
void * consumatore(void *);
void * visualizza(void *);

typedef struct {

    //  DONE: completare con i parametri da passare ai thread consumatori
    //
	VettoreProdCons* vpc;
	BufferMutuaEsclusione* bme;

} parametri_consumatore;

int main() {

    pthread_t produttori[NUM_PRODUTTORI];

    pthread_t consumatori[NUM_CONSUMATORI];
    
    pthread_t visualizzatore;

    VettoreProdCons * vettore = (VettoreProdCons*) malloc(sizeof(VettoreProdCons)); // DONE;

    BufferMutuaEsclusione * buffer = (BufferMutuaEsclusione*) malloc(sizeof(BufferMutuaEsclusione));// DONE;

    srand(getpid());

    // DONE: inizializzare le strutture e i relativi campi
    
	inizializza_vettore(vettore);
	inizializza_buffer(buffer);

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    parametri_consumatore * parametri = (parametri_consumatore*) malloc(sizeof(parametri_consumatore));// DONE;
	
	parametri->vpc=vettore;
	parametri->bme=buffer;

    for(int i=0; i<NUM_PRODUTTORI; i++) {

        // DONE: creare thread produttori
		pthread_create(&produttori[i],&attr,produttore,(void*)vettore);
    }

    for(int i=0; i<NUM_CONSUMATORI; i++) {

        // DONE: creare thread consumatori
    	pthread_create(&consumatori[i],&attr,consumatore,(void*)parametri);
	}
    
    // DONE: creare thread visualizzatore
	pthread_create(&visualizzatore,&attr,visualizza,(void*)buffer);
    // DONE: join delle 3 tipologie di thread

	for(int i=0; i<NUM_PRODUTTORI; i++) pthread_join(produttori[i],NULL);
	for(int i=0; i<NUM_CONSUMATORI; i++) pthread_join(consumatori[i],NULL);
	pthread_join(visualizzatore,NULL);

    // DONE: deallocazione strutture 
    
	rimuovi_vettore(vettore);
	rimuovi_buffer(buffer);
	pthread_attr_destroy(&attr);
    free(parametri);
	return 0;

}

void * produttore(void * p) {

    VettoreProdCons * vettore = (VettoreProdCons*) p; // DONE: prelievo parametri ;

    for(int i=0; i<PRODUZIONI; i++) {

        int valore = rand() % 10;

        printf("[PRODUTTORE] Produzione: %d\n", valore);

        produci(vettore, valore);
    }
    return NULL;
}

void * consumatore(void * p) {

    parametri_consumatore * parametri = (parametri_consumatore*) p;// DONE: prelievo parametri ;

    int valore;

    // DONE: consumare
	valore = consuma(parametri->vpc);
    printf("[CONSUMATORE] Consumazione: %d\n", valore);

    // DONE: aggiornare
	aggiorna_buffer(parametri->bme,valore);
    return NULL;
}

void * visualizza(void * p) {

     BufferMutuaEsclusione * buf = (BufferMutuaEsclusione*) p;// DONE: prelievo parametri ;

     for (int i=0; i< (NUM_PRODUTTORI*PRODUZIONI)/NUM_CONS; i++) {
                  
             int val;
             
             // DONE: stampare
			 val=stampa_valore(buf);
             
             printf("[VISUALIZZATORE]: La somma degli elementi consumati è: %d\n",val);
     
     }
     
     return NULL;

}
