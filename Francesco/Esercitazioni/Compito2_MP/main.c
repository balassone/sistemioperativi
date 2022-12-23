#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "header.h"

#define NUM_PRODUTTORI 2
#define NUM_CONSUMATORI 5

#define PRODUZIONI 10
#define CONSUMAZIONI 4

void produttore(VettoreProdCons * vettore);
void consumatore(VettoreProdCons * vettore, BufferMutuaEsclusione * buffer);

int main() {

	key_t shm_vett, shm_buf;
	shm_vett=IPC_PRIVATE;
	shm_buf=IPC_PRIVATE;
	int vett_shm=shmget(shm_vett,sizeof(VettoreProdCons),IPC_CREAT|0664);
    VettoreProdCons * vettore = (VettoreProdCons*) shmat(vett_shm,NULL,0);/* TBD: Allocare la struttura dati */
	int buf_shm=shmget(shm_buf,sizeof(BufferMutuaEsclusione),IPC_CREAT|0664);
    BufferMutuaEsclusione * buffer = shmat(buf_shm,NULL,0);/* TBD: Allocare la struttura dati */


    inizializza_vettore(vettore);
    inizializza_buffer(buffer);


    for(int i=0; i<NUM_PRODUTTORI; i++) {

        /* TBD: Creare i processi produttori, e fargli chiamare la
         *      funzione "produttore()"
         */
		 int pid=fork();
		 if(pid==0){
		 	produttore(vettore);
			exit(0);
		 }
    }


    for(int i=0; i<NUM_CONSUMATORI; i++) {

        /* TBD: Creare i processi consumatori, e fargli chiamare la
         *      funzione "consumatore()"
         */
		 int pid=fork();
		 if(pid==0){
			consumatore(vettore,buffer);
			exit(0);
		 }
    }


    /* TBD: Attendere la terminazione dei processi figli */

	for(int i=0; i<NUM_PRODUTTORI+NUM_CONSUMATORI; ++i) wait(NULL);
    rimuovi_buffer(buffer);
    rimuovi_vettore(vettore);


    /* TBD: De-allocare le strutture dati */
	shmctl(vett_shm,IPC_RMID,NULL);
	shmctl(buf_shm,IPC_RMID,NULL);
    return 0;

}

void produttore(VettoreProdCons * vettore) {

    srand(getpid());
    
    for(int i=0; i<PRODUZIONI; i++) {

        int valore = rand() % 10;

        printf("[MAIN PRODUTTORE] Produzione: %d\n", valore);

        /* TBD: Chiamare il metodo "produci()" del monitor */
		produci(vettore,valore);
    }

}

void consumatore(VettoreProdCons * vettore, BufferMutuaEsclusione * buffer) {

    srand(getpid());

    for(int i=0; i<CONSUMAZIONI; i++) {

        int valore;

        /* TBD: Chiamare il metodo "consuma()" del monitor */
		valore=consuma(vettore);
        printf("[MAIN CONSUMATORE] Consumazione: %d\n", valore);

        /* TBD: Chiamare il metodo "aggiorna()", passandogli 
         *      il valore che è stato appena consumato
         */
		 aggiorna(buffer,valore);
    }
}
