#include "procedure.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <wait.h>
int main(){
	key_t shm=IPC_PRIVATE;
	int id_shm=shmget(shm,sizeof(ProdCons),IPC_CREAT|0664);
	ProdCons* pc = (ProdCons*) shmat(id_shm,NULL,0);
	init_monitor(&(pc->m),2);
	pc->liberi=DIM;
	pc->occupati=0;
	for(int i=0; i<DIM; ++i){
		pc->stato[i]=LIBERO;
	}

	pid_t pid;

	for(int i=0; i<8; ++i){
		pid=fork();
		if(pid==0){
			int val = Consumo(pc);
			std::cout <<getpid() <<": Valore consumato: " << val << std::endl;
			exit(0);
		}
	}

	for(int i=0; i<8; ++i){
		pid=fork();
		if(pid==0){
			srand(getpid()*time(NULL));
			int val=rand()%100+1;
			std::cout <<getpid()<< ": Valore prodotto: " << val << std::endl;
			Produzione(pc,val);
		}
	}

	for(int i=0; i<16; ++i) wait(NULL);
	shmctl(id_shm,IPC_RMID,0);
	remove_monitor(&(pc->m));
	return 0;
}
