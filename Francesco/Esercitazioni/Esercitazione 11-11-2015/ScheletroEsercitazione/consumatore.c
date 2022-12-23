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
	printf("[Consumatore] Sono il processo consumatore con pid %d\n",getpid());
	key_t key = ftok(FTOK_PATH_Q, FTOK_CHAR_Q);
	int shmid = shmget(key,sizeof(BufferCircolare),IPC_CREAT|0664);
	BufferCircolare* bc = (BufferCircolare*) shmat(shmid,NULL,0);
	consuma_elementi(bc->semid,bc);
	sleep(2);
	consuma_elementi(bc->semid,bc);
	return 1;
}
