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

void Wait_Sem(int id_sem, int numsem)     {
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = 0;
	semop(id_sem,&sem_buf,1);
}


void Signal_Sem (int id_sem,int numsem)     {
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_op = 1;
	sem_buf.sem_flg = 0;
	semop(id_sem,&sem_buf,1);

}

// Consumo
void consuma(BufferCircolare* buf, int chiave, int semid){
	printf("[Consumatore %d] iniziato con chiave %d \n",getpid(), chiave);
	int sem;
	int value;
	int index;

	for(int i=0; i<3; i++){
		// DONE completare consumazione
		index=0;
		sem=chiave;
		Wait_Sem(semid,sem);
		Wait_Sem(semid,MUTEXC);
		while(index<SIZE && !(buf->stati[index]==OCCUPATO && buf->elementi[index].chiave==chiave)){
			index++;
		}
		buf->stati[index]=IN_USO;
		Signal_Sem(semid,MUTEXC);
		buf->stati[index]=LIBERO;
		printf("[Consumatore %d] consumo elemento in posizione %d\n",getpid(), index);	
		value=buf->elementi[index].valore;
		printf("[Consumatore %d] valore letto: %d\n",getpid(), value);
		Signal_Sem(semid,SPAZIO_DISP);
	}
}

//Produzione
void produci(BufferCircolare* buf, int chiave, int semid){
	printf("[Produttore %d] iniziato con chiave %d\n",getpid(), chiave);
	int val_sleep;
	int value;
	int sem;
	int index;

	for(int i=0; i<3; i++){
		val_sleep=rand()%3+1;
		sem=chiave; //MSG_DISP_N, il numero di semaforo corrisponde alla chiave
		// DONE COMPLETARE PRODUZIONE
		Wait_Sem(semid,SPAZIO_DISP); //Entro nel buffer quando è libero
		printf("[Produttore %d] entrato con chiave %d \n",getpid(), chiave);
		Wait_Sem(semid,MUTEXP); //Aspetto altri produttori per alterare lo stato.
		index=0;
		while(index<SIZE && buf->stati[index]!=LIBERO){
			index=index+1;
		}
		buf->stati[index]=IN_USO;
		Signal_Sem(semid,MUTEXP); //Permetto ad altri produttori ad accedere al vettore.
		sleep(val_sleep);
		value=rand()%100+1; //Calcolo il valore
		buf->elementi[index].chiave=chiave; //Copio la chiave
		buf->elementi[index].valore=value; //Copio il valore
		buf->stati[index]=OCCUPATO; //Aggiorno lo stato
		printf("[Produttore %d] ho prodotto %d, con chiave %d, in posizione %d\n",getpid(),value, chiave, index);
		Signal_Sem(semid,sem); //Segnalo la presenza di un messaggio al semaforo della chiave corrispondente
	}
}
