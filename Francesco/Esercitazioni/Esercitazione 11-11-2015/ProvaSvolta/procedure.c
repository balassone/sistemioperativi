			/*----IMPLEMENTAZIONE DELLE PROCEDURE----*/


#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <math.h>

//Procedure per la sincronizzazione sui semafori

void Wait_Sem(int id_sem, int numsem,int n)     {
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_op = -n;
	sem_buf.sem_flg = 0;
	semop(id_sem,&sem_buf,1);
}


void Signal_Sem (int id_sem,int numsem,int n)     {
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_op = n;
	sem_buf.sem_flg = 0;
	semop(id_sem,&sem_buf,1);

}

//Calcolo statistiche
double media(int* v){
	int i;
	double somma;
	somma = 0.0f;
	for(i = 0; i < N;i++){
		somma += v[i];
	}
	return (double)(somma/N);
}

double var(int* v,double media){
	int i;
	double somma_par,temp;
	somma_par = 0.0f;
	for(i = 0; i < N;i++){
		temp = v[i]*v[i];
		somma_par += (temp - media);
	}
	return (double)(somma_par/N-1);
}

// Consumo
void consuma_elementi(int sem, BufferCircolare* buf){
	int val[N];
	double m;
	int i;
	//Calcola media e varianza
	/*Qua va il codice della sincronizzazione*/	
	Wait_Sem(sem,NUM_MESS,N);
	for(i = 0; i < N; i++){
		val[i] = buf->elementi[i];
	}

	buf->testa = 0;
	Signal_Sem(sem,SPAZIO_DISP,N);
	printf("[Consumatore %d] consumo elementi\n",getpid());	
	m = media(val);
	printf("[Consumatore %d] media %f, varianza %f\n",getpid(),m,sqrt(var(val,m)));
}

//Produzione
void produci_elemento(int sem,BufferCircolare* buf){
	int val;
	val =  (1+rand()%11);
	Wait_Sem(sem,SPAZIO_DISP,1);
	Wait_Sem(sem,MUTEXP,1);
	buf->elementi[buf->testa] = val;
	printf("[Produttore %d] ho prodotto %d in posizione %d\n",getpid(),val,buf->testa);
	buf->testa = ++(buf->testa) % N;
	Signal_Sem(sem,MUTEXP,1);
	Signal_Sem(sem,NUM_MESS,1);
}
