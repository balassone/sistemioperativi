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
	BufferCircolare* buf;

	key_t key_shm=IPC_PRIVATE,key_sem=IPC_PRIVATE;
	key_shm=IPC_PRIVATE; //DONE;
	key_sem=IPC_PRIVATE; //DONE;

	shmid = shmget(key_shm,sizeof(BufferCircolare),IPC_CREAT|0664); //DONE;
	semid = semget(key_sem,6,IPC_CREAT|0664); //DONE;

	printf("[MASTER] - Shmid : %d, Semid: %d\n",shmid,semid);

	// DONE
	// Inizializzare risorse
	buf = (BufferCircolare*) shmat(shmid,NULL,0);
	for(int j=0; j<SIZE; ++j){
		buf->stati[j]=LIBERO;
	}
	if(buf<0) perror("Errore Buffer-SHM!");

	semctl(semid,SPAZIO_DISP,SETVAL,SIZE);
	semctl(semid,MSG_DISP_1,SETVAL,0);
	semctl(semid,MSG_DISP_2,SETVAL,0);
	semctl(semid,MSG_DISP_3,SETVAL,0);
	semctl(semid,MUTEXC,SETVAL,1);
	semctl(semid,MUTEXP,SETVAL,1);


	srand(time(NULL));
	int val;
	for(i = 0; i < NCONS+NPROD; i++){
		// DONE CREARE PROCESSI FIGLI (PRODUTTORI E CONSUMATORI)
		val =  (1+rand()%3);
		sleep(val);
		if(i<3){
			pid=fork();
			if(pid==0){
				srand(getpid()*time(NULL));
				consuma(buf,i+1,semid);
				exit(0);
			}
		} else {
			pid=fork();
			if(pid==0){
				srand(getpid()*time(NULL));
				produci(buf,i-2,semid);
				exit(0);
			}
		}

	}
	
	for(i = 0; i < NCONS+NPROD ; i++){
		pid_ex=wait(&st); // DONE JOIN COMPLETAMENTO FIGLI
		printf("[MASTER] - Il processo %d ha terminato l'esecuzione\n",pid_ex);			
	}

	// DONE RIMOZIONE RISORSE
	semctl(semid,0,IPC_RMID);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
