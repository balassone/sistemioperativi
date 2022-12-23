#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

#include "header.h"
#define N 10
int main(){
	pthread_t lettori[N];
	pthread_t scrittori[N];

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

	LettScritt* ls = (LettScritt*) malloc(sizeof(LettScritt));

	ls->buffer=0;
	ls->numlettori=0;
	ls->numscrittori=0;
	ls->lettori_wait=0;
	ls->scrittori_wait=0;

	pthread_mutex_init(&(ls->mutex),NULL);
	pthread_cond_init(&(ls->cv_lett),NULL);
	pthread_cond_init(&(ls->cv_scritt),NULL);

	for(int i=0; i<N+N; ++i){
		if(i<N){
			pthread_create(&lettori[i],&attr,Scrittore,(void*)ls);
		}
		else{
			pthread_create(&scrittori[i/2],&attr,Lettore,(void*)ls);
		}
	}
	for(int i=0; i<N; ++i) {
		pthread_join(scrittori[i],NULL);
		pthread_join(lettori[i],NULL);
	}
	pthread_mutex_destroy(&(ls->mutex));
	pthread_cond_destroy(&(ls->cv_lett));
	pthread_cond_destroy(&(ls->cv_scritt));
	free(ls);
	pthread_attr_destroy(&attr);

	pthread_exit(0);
}
