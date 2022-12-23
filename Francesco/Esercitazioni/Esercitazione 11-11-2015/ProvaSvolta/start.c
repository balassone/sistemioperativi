#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "header.h"

#define N_PROC 11


int main(){
	pid_t pid_ex,pid;
	int st,i;
	int shmid,semid;
	
	key_t key_shm,key_sem;
	key_shm = ftok(PATH_SHM,CHAR_SHM);
	key_sem = ftok(PATH_SEM,CHAR_SEM);

	shmid = shmget(key_shm,sizeof(BufferCircolare),IPC_CREAT | 0664);
	semid = semget(key_sem,3,IPC_CREAT | 0664);
	printf("[MASTER] - Shmid : %d, Semid: %d\n",shmid,semid);	
	semctl(semid,SPAZIO_DISP,SETVAL,N);
	semctl(semid,NUM_MESS,SETVAL,0);
	semctl(semid,MUTEXP,SETVAL,1);

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
	shmctl(shmid,IPC_RMID,0);
	semctl(semid,0,IPC_RMID);
	return 0;
}
