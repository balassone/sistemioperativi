#include <iostream>
#include <stdexcept>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "semafori.h"
#include "procedure.h"
using std::cout;
using std::endl;
using std::runtime_error;
int main(){
	key_t shm_key{IPC_PRIVATE}, sem_key{IPC_PRIVATE};
	int ds_shm = shmget(shm_key, sizeof(int), IPC_CREAT|0664);
	if(ds_shm<0) throw runtime_error("SHM!!!");
	int ds_sem = semget (sem_key, 2, IPC_CREAT|0664);
	if(ds_sem<0) throw runtime_error("SHM!!");
	int* p = (int*) shmat(ds_shm,NULL,0);
	semctl(ds_sem,SPAZIO_DISPONIBILE,SETVAL,1);
	semctl(ds_sem,MESSAGGIO_DISPONIBILE, SETVAL,0);
	pid_t pid=fork();
	if(pid==0){
		consumatore(p, ds_sem);
		exit(0);
	}
	pid=fork();
	if(pid==0){
		produttore(p,ds_sem);
		exit(0);
	}
	for(int i=0; i<2; ++i) wait(NULL);
	shmctl(ds_shm,IPC_RMID,NULL);
	semctl(ds_sem,0,IPC_RMID);
	return 0;
}
