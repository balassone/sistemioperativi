#include <iostream>
#include "semafori.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <stdexcept>
int main(){
	key_t shm_key{IPC_PRIVATE}, sem_key{IPC_PRIVATE};
	int ds_shm=shmget(shm_key,sizeof(int),IPC_CREAT|0664);
	if(ds_shm<0) throw std::runtime_error("Errore SHM!");
	int* buf=(int*)shmat(ds_shm,NULL,0);
	if(buf==(void*)-1) throw std::runtime_error("Errore SHMAT!");
	int ds_sem=semget(sem_key,1,IPC_CREAT|0664);
	if(ds_sem<0) throw std::runtime_error("Errore SEM!");
	semctl(ds_sem,0,SETVAL,1);
	*buf=0;
	for(int i=0; i<2; ++i){
		pid_t pid=fork();
		if(pid<0) throw std::runtime_error("Errore Fork!");
		if(pid==0){
			std::cout << "Processo " << i << " creato!" << std::endl;
			for(int j=0; j<100; ++j){
				Wait_Sem(ds_sem,0);
				int tmp=*buf;
				std::cout << "Processo " << i << " legge " << tmp << std::endl;
				*buf=tmp+1;
				std::cout << "Processo " << i << " ha incrementato\n";
				Signal_Sem(ds_sem,0);
			}
			exit(0);
		}
	}
	for(int i=0; i<2; ++i) wait(NULL);
	std::cout << "Valore finale: " << *buf << std::endl;
	shmctl(ds_shm,IPC_RMID,0);
	semctl(ds_sem,0,IPC_RMID);
	return 0;

}
