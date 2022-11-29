#include <iostream>
#include "header.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_THREADS 10

int main(){
	pthread_attr_t attr;
	pthread_t threads[NUM_THREADS];
	ProdCons* pc = new ProdCons;

	pthread_mutex_init(&pc->mutex,NULL);
	pthread_cond_init(&pc->ok_prod_cv,NULL);
	pthread_cond_init(&pc->ok_cons_cv,NULL);

	pc->ok_produzione=1;
	pc->ok_consumo=0;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	int k;
	for(k=0; k<NUM_THREADS; k++){
		if(k%2){
			std::cout << "Thread consumatore " << k << "\n";
			pthread_create(&threads[k],&attr,Consumatore,(void*)pc);
		} else {
			sleep(1);
			std::cout << "Thread produttore " << k << "\n";
			pthread_create(&threads[k],&attr,Produttore,(void*)pc);
		}
	}

	for(k=0; k<NUM_THREADS; k++){
		pthread_join(threads[k],NULL);
		std::cout << "Thread " << k << " terminato\n";
	}

	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&pc->mutex);
	pthread_cond_destroy(&pc->ok_prod_cv);
	pthread_cond_destroy(&pc->ok_cons_cv);

	delete[] pc;
	pthread_exit(0);

}
