#include "header.h"
#include <sys/ipc.h>
#include <sys/sem.h>
void inizializza_vettore(VettoreProdCons* vett){
	vett->testa=0;
	vett->coda=0;
	init_monitor(&vett->m,2);
}

void produci(VettoreProdCons* vett, int valore){
	//enter monitor
	enter_monitor(&vett->m);
	//if vettore pieno->wait
	if((vett->testa+1)%DIM==vett->coda){
		wait_condition(&vett->m,CV_PROD);
	}
	vett->buffer[vett->testa]=valore;
	vett->testa=vett->testa+1 % DIM;
	signal_condition(&vett->m,CV_CONS);
	leave_monitor(&vett->m);
}

int consuma(VettoreProdCons* vett){
	int valore;
	enter_monitor(&vett->m);
	if(vett->testa==vett->coda){
		wait_condition(&vett->m,CV_CONS);
	}
	valore=vett->buffer[vett->coda];
	vett->coda=vett->coda+1 % DIM;
	signal_condition(&vett->m,CV_PROD);
	leave_monitor(&vett->m);
	return valore;
}

void rimuovi_vettore(VettoreProdCons* vett){
	remove_monitor(&vett->m);
}

void inizializza_buffer(BufferMutuaEx* buff){
	key_t key_mutex=IPC_PRIVATE;
	buff->semid=semget(key_mutex,1,IPC_CREAT|0664);
	semctl(buff->semid,0,SETVAL,1);
	buff->valore=0;
}

void rimuovi_buffer(BufferMutuaEx* buff){
	semctl(buff->semid,0,IPC_RMID);
}

void aggiorna_buffer(BufferMutuaEx* buff, int val){
	struct sembuf sem_buf;
	sem_buf.sem_num=MUTEX;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=-1;
	semop(buff->semid,&sem_buf,1);
	buff->valore=buff->valore+val;
	
	sem_buf.sem_num=MUTEX;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=1;
	semop(buff->semid,&sem_buf,1);
}
