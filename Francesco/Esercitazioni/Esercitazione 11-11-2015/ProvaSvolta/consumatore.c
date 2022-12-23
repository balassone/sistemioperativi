/*PROCESSO CONSUMATORE*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"


int main(){
        int shmid,semid,i;
        key_t key_shm,key_sem;
	BufferCircolare* b;
        key_shm = ftok(PATH_SHM,CHAR_SHM);
        key_sem = ftok(PATH_SEM,CHAR_SEM);

	shmid = shmget(key_shm,0,IPC_CREAT | 0664);
	semid = semget(key_sem,0,IPC_CREAT | 0664);
	printf("[Consumatore] Sono il processo consumatore con pid %d,shmid = %d,semid = %d\n",getpid(),shmid,semid);
	b = (BufferCircolare*) shmat(shmid,0,0);
	for(i = 0; i < 2; i++){
		consuma_elementi(semid,b);
	}	
	return 1;
}
