#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "semafori.h"
#include "procedure.h"
using std::cout;
using std::endl;
int main(){
	key_t shm_key{IPC_PRIVATE}, sem_key{IPC_PRIVATE};
	int ds_shm=shmget(shm_key,sizeof(struct prodcons), IPC_CREAT|0664);
	if(ds_shm<0) cout << "Errore shm";
	int ds_sem=semget(sem_key,4,IPC_CREAT|0664);
	if(ds_sem<0) cout << "Errore sem";
	struct prodcons* pc = (struct prodcons*) shmat(ds_shm,NULL,0);
	pc->testa=0;
	pc->coda=0;
	semctl(ds_sem,SPAZIO_DISPONIBILE,SETVAL,DIM_BUFFER);
	semctl(ds_sem,NUM_MESSAGGI,SETVAL,0);
	semctl(ds_sem,MUTEXC,SETVAL,1);
	semctl(ds_sem,MUTEXP,SETVAL,1);

	for(int i{0}; i<NUMCONSUMATORI; ++i){
		pid_t pid=fork();
		if(pid<0) cout << "Errore fork";
		if(pid==0){
			srand(getpid()*time(NULL));
			cout << "Inizia consumatore " << i << "...";
			consumatore(pc,ds_sem);
			exit(0);
		}	
	}
	for(int i{0}; i<NUMPRODUTTORI; ++i){
		pid_t pid=fork();
		if(pid<0) cout << "Errore fork";
		if(pid==0){
			srand(getpid()*time(NULL));
			cout << "Inizia produttore...";
			produttore(pc, ds_sem);
			exit(0);
		}
	}

	for(int i{0}; i<(NUMPRODUTTORI+NUMCONSUMATORI); ++i){
		wait(NULL);
	}
	semctl(ds_sem,0,IPC_RMID);
	shmctl(ds_shm,IPC_RMID,NULL);
	return 0;
}
