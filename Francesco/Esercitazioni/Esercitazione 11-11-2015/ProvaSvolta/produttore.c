/* PROCESSO PRODUTTORE */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"
#include <time.h>

int main(){
	int shmid,semid;
	
	srand(time(NULL));
	BufferCircolare* b;
	key_t key_shm,key_sem;
	key_shm = ftok(PATH_SHM,CHAR_SHM);
        key_sem = ftok(PATH_SEM,CHAR_SEM);

	shmid = shmget(key_shm,0,IPC_CREAT | 0664);
	semid = semget(key_sem,0,IPC_CREAT | 0664);

	printf("[PRODUTTORE] <%d> shmid = %d, semid = %d\n",getpid(),shmid,semid);
	b = (BufferCircolare*) shmat(shmid,0,0);
	produci_elemento(semid,b);
	return 1;
}
