#include <iostream>
#include "semafori.h"
#include "procedure.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

using std::cin;
using std::cout;
using std::endl;

int main(){
	key_t shm_key{IPC_PRIVATE}, sem_key{IPC_PRIVATE};
	int ds_shm=shmget(shm_key,sizeof(struct prodcons),IPC_CREAT|0664);
	if(ds_shm<0) return 1;
	int ds_sem=semget(sem_key,4,IPC_CREAT|0664);
	if(ds_sem<0) return 2;

	struct prodcons* p = (struct prodcons*) shmat(ds_shm,NULL,0);
	for(int i{0}; i<DIM_BUFFER; ++i) p->stato[i]=BUFFER_VUOTO;
	semctl(ds_sem,MUTEXC,SETVAL,1);
	semctl(ds_sem,MUTEXP,SETVAL,1);
	semctl(ds_sem,SPAZIO_DISP,SETVAL,DIM_BUFFER);
	semctl(ds_sem,NUM_MESSAGGI,SETVAL,0);

	for(int i{0}; i<NUMCONSUMATORI; ++i){
		pid_t pid=fork();
		if(pid<0) return 3;
		if(pid==0){
			cout << "Consumatore " << i << " parte...\n";
			srand(getpid()*time(NULL));
			consumatore(p,ds_sem);
			exit(0);
		}
	}

	for(int i{0}; i<NUMPRODUTTORI; ++i){
		pid_t pid=fork();
		if(pid<0) return 4;
		if(pid==0){
			cout << "Produttore " << i << " parte...\n";
			srand(getpid()*time(NULL));
			produttore(p,ds_sem);
			exit(0);
		}
	}
	for(int i{0}; i<(NUMPRODUTTORI+NUMCONSUMATORI); ++i) wait(NULL);
	semctl(ds_sem,0,IPC_RMID);
	shmctl(ds_shm,IPC_RMID,NULL);
	return 0;
}
