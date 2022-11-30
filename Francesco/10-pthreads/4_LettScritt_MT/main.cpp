#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include "procedure.h"
#define NUM_THREADS 10

using std::cout;

int main(){

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_t threads[NUM_THREADS];

	LettScritt* ls = new LettScritt;

	pthread_mutex_init(&ls->mutex,NULL);
	pthread_cond_init(&(ls->ok_scritt_cv),NULL);
	pthread_cond_init(&ls->ok_lett_cv,NULL);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	ls->numlettori=0;
	ls->numscrittori=0;
	ls->num_lettori_wait=0;
	ls->num_scrittori_wait=0;
	ls->mess=0;
	
	for(int i{0}; i<NUM_THREADS; ++i){
		if(i%2){
			pthread_create(&threads[i],&attr,Lettore,(void*)ls);
		} else {
			sleep(1);
			pthread_create(&threads[i],&attr,Scrittore,(void*)ls);
		}
	}

	for(int i{0}; i<NUM_THREADS; ++i){
		pthread_join(threads[i],NULL);
	}

	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&ls->mutex);
	pthread_cond_destroy(&ls->ok_scritt_cv);
	pthread_cond_destroy(&ls->ok_lett_cv);
	delete ls;
	pthread_exit(NULL);
}
