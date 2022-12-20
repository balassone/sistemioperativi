#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

#include "header.h"


int main(){
	pid_t pid_ex,pid;
	int st,i;
	int shmid,semid;
	BufferMutuaEx* buf;

	key_t key_shm,key_sem;
	key_shm = IPC_PRIVATE;
	key_sem = IPC_PRIVATE;

	shmid = shmget(key_shm,sizeof(BufferMutuaEx),IPC_CREAT|0664); 
	semid = semget(key_sem,5,IPC_CREAT|0664); 
	
	printf("[MASTER] - Shmid : %d, Semid: %d\n",shmid,semid);

	// TODO: inizializzare semafori
	semctl(semid,SPAZIO_DISP,SETVAL,DIM);
	semctl(semid,MSG1_DISP,SETVAL,0);
	semctl(semid,MSG2_DISP,SETVAL,0);
	semctl(semid,MUTEXC,SETVAL,1);
	semctl(semid,MUTEXP,SETVAL,1);

	buf = (BufferMutuaEx*) shmat(shmid,NULL,0);// TODO 
	
	// TODO: inizializzazione della struttura
	for(i=0; i<DIM; ++i){

		buf->stato[i]=LIBERO;

	}
	srand(time(NULL));

	for(i = 0; i < NPROD; i++){
		pid = fork();
		
		// TODO: ogni figlio produttore (1 e 2) fa PRODS produzioni
		
		if(pid<0) perror("Errore Fork produttori!\n");

		if(pid==0){
			if(i<2){
				for(int j=0; j<PRODS; ++j){
					
					int val=(i+j)*(rand()%50); //i+j per non generare numeri uguali
					produci_tipo_1(buf,semid,val);

				}
			} else {
				for(int j=0; j<PRODS; ++j){

					int val=(i+j)*(rand()%50); //i+j per non generare numeri uguali
					produci_tipo_2(buf,semid,val);

				}
			}
			exit(0);
		}

	}

	for(i = 0; i < NCONS; i++){
		pid = fork();
		// TODO: ogni figlio consumatore (1 e 2) fa CONS consumi
		if(pid<0) perror("Errore Fork Consumatori!\n");
		if(pid==0){
			if(i<1){
				for(int j=0; j<CONS; ++j){

					consuma_tipo_1(buf,semid);

				}
			} else {
				for(int j=0; j<CONS; ++j){

					consuma_tipo_2(buf,semid);

				}
			}
			exit(0);
		}
	}
	
	// TODO: attesa completamento figli
	for(i=0; i<NPROD+NCONS; ++i){

		pid_ex=wait(&st);

		printf("[MASTER] Terminato processo %d con stato %d\n",pid_ex,st);

	}

	// TODO: rimozione strutture 
	semctl(semid,0,IPC_RMID);
	shmctl(shmid,IPC_RMID,NULL);

	return 0;
}

