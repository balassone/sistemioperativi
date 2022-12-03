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

    //  TODO: completare con i parametri da passare ai thread consumatori
    //

} parametri_consumatore;

int main() {

    pthread_t produttori[NUM_PRODUTTORI];

    pthread_t consumatori[NUM_CONSUMATORI];
    
    pthread_t visualizzatore;

    VettoreProdCons * vettore = // TODO;

    BufferMutuaEsclusione * buffer = // TODO;

    srand(getpid());

    // TODO: inizializzare le strutture e i relativi campi
    
    parametri_consumatore * parametri = // TODO;


    for(int i=0; i<NUM_PRODUTTORI; i++) {

        // TODO: creare thread produttori
    }

    for(int i=0; i<NUM_CONSUMATORI; i++) {

        // TODO: creare thread consumatori
    }
    
    // TODO: creare thread visualizzatore

    // TODO: join delle 3 tipologie di thread

    // TODO: deallocazione strutture 
    
    return 0;

}

void * produttore(void * p) {

    VettoreProdCons * vettore = // TODO: prelievo parametri ;

    for(int i=0; i<PRODUZIONI; i++) {

        int valore = rand() % 10;

        printf("[PRODUTTORE] Produzione: %d\n", valore);

        produci(vettore, valore);
    }

    return NULL;
}

void * consumatore(void * p) {

    parametri_consumatore * parametri = // TODO: prelievo parametri ;

    int valore;

    // TODO: consumare

    printf("[CONSUMATORE] Consumazione: %d\n", valore);

    // TODO: aggiornare

    return NULL;
}

void * visualizza(void * p) {

     BufferMutuaEsclusione * buf = // TODO: prelievo parametri ;

     for (int i=0; i< (NUM_PRODUTTORI*PRODUZIONI)/NUM_CONS; i++) {
                  
             int val;
             
             // TODO: stampare
             
             printf("[VISUALIZZATORE]: La somma degli elementi consumati è: %d\n",val);
     
     }
     
     return NULL;

}