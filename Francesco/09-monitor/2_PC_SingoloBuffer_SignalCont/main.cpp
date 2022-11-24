#include "procedure.h"
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#define PRODUTTORI 1
#define CONSUMATORI 1

int main(){
	
	key_t shm_key=IPC_PRIVATE;

	int shmid=shmget(shm_key, sizeof(ProdCons), IPC_CREAT|0664);

	ProdCons* pc = (ProdCons*) shmat(shmid,NULL,0);

	init_monitor(&(pc->m),2);
	pc->buffer_vuoto=1;
	pc->buffer_pieno=0;
	srand(time(NULL));
	pid_t pid;
	for(int i{0}; i<CONSUMATORI; ++i){
		pid=fork();
		if(pid==0){
			int val = consuma(pc);
			std::cout << "Valore consumato: "<< val << std::endl;
			exit(0);
		}
	}

	for(int i{0}; i<PRODUTTORI; ++i){
		pid=fork();
		if(pid==0){
			int val = rand()%100+1;
			produci(pc,val);
			std::cout << "Valore prodotto: " << val << std::endl;
			exit(0);
		}
	}

	for(int i{0}; i<PRODUTTORI+CONSUMATORI; ++i){
		wait(NULL);
	}
	remove_monitor(&(pc->m));
	shmctl(shmid,IPC_RMID,0);
	return 0;
}
