#include "procedure.h"
#include <iostream>
#include <time.h>
#include <unistd.h>
void Scrivi(LettScritt* ls,msg mess){
	InizioScrittura(ls);

	ls->mess=mess;
	std::cout << "Ho appena scritto: " << mess << std::endl;
	FineScrittura(ls);
}

msg Leggi(LettScritt* ls){
	InizioLettura(ls);
	msg mess=ls->mess;
	std::cout << "Ho appena letto: " << mess << std::endl;
	FineLettura(ls);
	return mess;
}

void InizioLettura(LettScritt* ls){

	pthread_mutex_lock(&(ls->mutex));

	while(ls->numscrittori>0){
		ls->num_lettori_wait++;
		pthread_cond_wait(&(ls->ok_lett_cv),&(ls->mutex));
		ls->num_lettori_wait--;
	}
	ls->numlettori++;
	pthread_cond_signal(&(ls->ok_lett_cv));
	pthread_mutex_unlock(&(ls->mutex));

}

void FineLettura(LettScritt* ls){
	pthread_mutex_lock(&(ls->mutex));
	ls->numlettori--;
	if(ls->numlettori==0) pthread_cond_signal(&(ls->ok_scritt_cv));
	pthread_mutex_unlock(&(ls->mutex));
}

void InizioScrittura(LettScritt* ls){
	pthread_mutex_lock(&(ls->mutex));
	while(ls->numlettori>0 || ls->numscrittori>0){
		ls->num_scrittori_wait++;
		pthread_cond_wait(&(ls->ok_scritt_cv),&(ls->mutex));
		ls->num_scrittori_wait--;
	}
	ls->numscrittori++;
	pthread_mutex_unlock(&(ls->mutex));
}

void FineScrittura(LettScritt* ls){
	pthread_mutex_lock(&(ls->mutex));
	ls->numscrittori--;
	if(ls->num_scrittori_wait>0) pthread_cond_signal(&(ls->ok_scritt_cv));
	else pthread_cond_signal(&(ls->ok_lett_cv));
	pthread_mutex_unlock(&(ls->mutex));
}

void* Lettore(void* p){
	LettScritt* ls=(LettScritt*)p;
	
	for(int i=0; i<3; i++){
		Leggi(ls);
	}

	pthread_exit(NULL);
}

void* Scrittore(void* p){
	LettScritt* ls = (LettScritt*) p;
	srand(time(NULL));
	for(int i=0; i<3; ++i){
		msg a = rand()%100+1;
		Scrivi(ls,a);
	}
	pthread_exit(NULL);
}
