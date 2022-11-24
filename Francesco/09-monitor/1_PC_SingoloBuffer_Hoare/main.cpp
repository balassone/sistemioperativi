#include <iostream>
#include "monitor_hoare.h"
#include "procedure.h"
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/shm.h>
int main(){
	key_t key_shm{IPC_PRIVATE};
	int shmid=shmget(key_shm,sizeof(ProdCons),IPC_CREAT|0664);
	ProdCons* pc = (ProdCons*) shmat(shmid,NULL,0);
	init_monitor(&(pc->m),2);
	pc->buffer_libero=1;
	pc->buffer_occupato=0;
	int val{5};

	pid_t pid=fork();
	
	if(pid==0){
		std::cout << Consuma(pc) << std::endl;
		exit(0);
	}

	pid=fork();

	if(pid==0){
		Produci(pc,val);
		exit(0);
	}

	for (int i=0; i<2; ++i){
		wait(NULL);
	}
	remove_monitor(&(pc->m));
	shmctl(shmid,IPC_RMID,0);
	return 0;
}
