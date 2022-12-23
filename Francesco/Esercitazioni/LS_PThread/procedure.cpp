#include "header.h"
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void inizioLettura(LettScritt* ls){
	pthread_mutex_lock(&(ls->mutex));
	while(ls->numscrittori>0){
		ls->lettori_wait++;
		pthread_cond_wait(&(ls->cv_lett),&(ls->mutex));
		ls->lettori_wait--;
	}
	ls->numlettori=ls->numlettori+1;
	pthread_mutex_unlock(&(ls->mutex));
}

void fineLettura(LettScritt* ls){
	pthread_mutex_lock(&(ls->mutex));
	ls->numlettori=ls->numlettori-1;
	if(ls->numlettori==0) pthread_cond_signal(&(ls->cv_scritt));
	pthread_mutex_unlock(&(ls->mutex));
}

void inizioScrittura(LettScritt* ls){
	pthread_mutex_lock(&(ls->mutex));

	while(ls->numlettori>0 || ls->numscrittori>0){
		ls->scrittori_wait++;
		pthread_cond_wait(&(ls->cv_scritt),&(ls->mutex));
		ls->scrittori_wait--;
	}

	ls->numscrittori=ls->numscrittori+1;

	pthread_mutex_unlock(&(ls->mutex));
}

void fineScrittura(LettScritt* ls){
	pthread_mutex_lock(&(ls->mutex));

	ls->numscrittori=ls->numscrittori-1;

	if(ls->scrittori_wait>0) pthread_cond_signal(&(ls->cv_scritt));
	else pthread_cond_broadcast(&(ls->cv_lett));

	pthread_mutex_unlock(&(ls->mutex));
}

void Scrivi(LettScritt* ls, int val){
	inizioScrittura(ls);
	int myid=gettid();
	printf("[%d] Scrivo il valore: %d\n",myid,val);
	ls->buffer=val;
	fineScrittura(ls);
}

int Leggi(LettScritt* ls){
	inizioLettura(ls);
	int val=ls->buffer;
	int myid=gettid();
	printf("[%d] Leggo il valore: %d\n",myid,val);
	fineLettura(ls);
	return val;
}

void* Lettore(void* p){
	LettScritt* ls = (LettScritt*) p;
	Leggi(ls);
	pthread_exit(0);
}
void* Scrittore(void* p){
	LettScritt* ls = (LettScritt*) p;
	srand(gettid());
	int val=rand()%100;
	Scrivi(ls,val);
	pthread_exit(0);
}
