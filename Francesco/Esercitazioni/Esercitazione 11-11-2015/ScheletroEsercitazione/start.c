#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "header.h"

#define N_PROC 2


int main(){
	pid_t pid_ex,pid;
	int st,i;
	//Istanziamo
	key_t key = ftok(FTOK_PATH_Q, FTOK_CHAR_Q);
	int shmid=shmget(key,sizeof(BufferCircolare),IPC_CREAT|0664);
	BufferCircolare* buf=(BufferCircolare*) shmat(shmid,NULL,0);
	buf->semid=semget(key,3,IPC_CREAT|0664);
	semctl(buf->semid,MUTEXP,SETVAL,0);
	semctl(buf->semid,SPAZIO_DISP,SETVAL,N);
	semctl(buf->semid,NUM_MESS,SETVAL,0);


	buf->testa=0;
	buf->coda=0;
	for(int i=0; i<N; ++i) buf->elementi[i]=0;

	for(i = 0; i < N_PROC;i++){
		pid = fork();
		if(pid == 0){
			if(i == 0){
			//Instanzia consumatore
				execl("./consumatore","./consumatore",NULL);
			}else{
			//Instanzia produttore
				execl("./produttore","./produttore",NULL);
			}
			_exit(0);			
		}
		sleep(1);

	}
	
	for(i = 0; i < N_PROC ; i++){
		pid_ex = wait(&st);
		printf("[MASTER] - Il processo %d ha terminato l'esecuzione\n",pid_ex);			
	}
	semctl(buf->semid,0,IPC_RMID);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
