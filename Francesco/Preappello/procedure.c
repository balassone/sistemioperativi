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
#include "semafori.h"
#include <math.h>

void produci_tipo_1(BufferMutuaEx * buf, int semid, int value) {

	// TODO: completare produzione 1
	Wait_Sem(semid,SPAZIO_DISP);

	int index=0;

	Wait_Sem(semid,MUTEXP);
	
	while(index<DIM && buf->stato[index]!=LIBERO) index++;

	buf->stato[index]=IN_USO;
	
	sleep(1+rand()%3);
	Signal_Sem(semid,MUTEXP);
	
	buf->buffer[index]=value;
	buf->stato[index]=OCC_TIPO1;
	
	printf("[Produttore %d] ho prodotto %d di tipo 1, in posizione %d\n", getpid(), value, index);
	
	Signal_Sem(semid,MSG1_DISP);
}

void produci_tipo_2(BufferMutuaEx * buf, int semid, int value) {

	// TODO: completare produzione 2 
	Wait_Sem(semid,SPAZIO_DISP);

	int index=0;

	Wait_Sem(semid,MUTEXP);

	while(index<DIM && buf->stato[index]!=LIBERO) index++;

	buf->stato[index]=IN_USO;
	
	sleep(1+rand()%3);
	Signal_Sem(semid,MUTEXP);

	buf->buffer[index]=value;
	buf->stato[index]=OCC_TIPO2;
	printf("[Produttore %d] ho prodotto %d di tipo 2, in posizione %d\n", getpid(), value, index);
	
	Signal_Sem(semid,MSG2_DISP);
}

void consuma_tipo_1(BufferMutuaEx * buf, int semid) {

	// TODO: completare consumo 1
	Wait_Sem(semid,MSG1_DISP);

	int index=0;

	Wait_Sem(semid,MUTEXC);

	while(index<DIM && buf->stato[index]!=OCC_TIPO1) index++;

	buf->stato[index]=IN_USO;
	
	sleep(1+rand()%3);
	Signal_Sem(semid,MUTEXC);

	int value = buf->buffer[index];
	buf->stato[index]=LIBERO;
	printf("[Consumatore %d] consumo elemento %d di tipo 1 in posizione %d\n",getpid(), value, index);	
	
	Signal_Sem(semid,SPAZIO_DISP);
}

void consuma_tipo_2(BufferMutuaEx * buf, int semid) {
	
	// TODO: completare consumo 2
	Wait_Sem(semid,MSG2_DISP);

	int index=0;

	Wait_Sem(semid,MUTEXC);

	while(index<DIM && buf->stato[index]!=OCC_TIPO2) index++;

	buf->stato[index]=IN_USO;
	
	sleep(1+rand()%3);
	Signal_Sem(semid,MUTEXC);

	int value = buf->buffer[index];
	buf->stato[index]=LIBERO;
	printf("[Consumatore %d] consumo elemento %d di tipo 2 in posizione %d\n",getpid(), value, index);	
	
	Signal_Sem(semid,SPAZIO_DISP);
}
