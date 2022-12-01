#include "procedure.h"
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREAD_PROD 3
#define NUM_THREAD_CONS 3
#define NUM_PRODUZIONI 10
#define NUM_CONSUMAZIONI 10
#define CONTEGGIO 5

void* thread_produttore(void*);
void* thread_consumatore(void*);
void* thread_conteggio(void*);
//THREAD=>MALLOC
int main(){
	MonitorProdCons* m = (MonitorProdCons*) malloc(sizeof(MonitorProdCons));
	
	pthread_t produttore[NUM_THREAD_PROD];
	pthread_t consumatore[NUM_THREAD_CONS];
	pthread_t conteggio;
	init_monitor(m);
	
	for(int i=0;i<NUM_THREAD_PROD; i++){
		pthread_create(&produttore[i],NULL,thread_produttore,(void*) m);
	}

	for(int i=0; i<NUM_THREAD_CONS; i++){
		pthread_create(&consumatore[i],NULL,thread_consumatore,(void*)m);
	}

	pthread_create(&conteggio,NULL,thread_conteggio,(void*)m);
	
	for(int i=0; i<NUM_THREAD_PROD; i++){
		pthread_join(produttore[i],NULL); //NON SERVE PIU' RIFERIMENTO
	}

	for(int i=0; i<NUM_THREAD_CONS; i++){
		pthread_join(consumatore[i],NULL);
	}

	pthread_join(conteggio,NULL);

	remove_monitor(m);
	free(m);
	pthread_exit(NULL);
}

void* thread_produttore(void* x){
	MonitorProdCons* m=(MonitorProdCons*) x;
	for(int i=0; i<NUM_PRODUZIONI; i++){
		int val = rand()%10;
		produzione(m,val);
		printf("[PRODUTTORE] Ho prodotto %d\n",val);
	}
	pthread_exit(0);
}

void* thread_consumatore(void* x){
	MonitorProdCons* m = (MonitorProdCons*) x;
	for(int i=0; i<NUM_CONSUMAZIONI; i++){
		printf("[CONSUMATORE] Ho consumato %d\n",consumazione(m));
	}
	pthread_exit(0);
}

void* thread_conteggio(void* x){
	//Troppo lungo non ho visto
	MonitorProdCons* m = (MonitorProdCons*) x;
	int consumazioni_effettuate=0;
	int conteggio;
	pthread_exit(0);
}
