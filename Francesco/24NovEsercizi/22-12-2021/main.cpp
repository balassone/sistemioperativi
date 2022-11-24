// Creiamo due memorie condivise, in una di esse metteremo il monitor.
// Nell'altra metteremo il buffer in mutex, useremo semafori.
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include<stdio.h>
#include <stdlib.h>
#include "header.h"
#define TOKEN1 'a'
#define TOKEN2 'b'
void produttore(VettoreProdCons* vett);
void consumatore(VettoreProdCons* vett, BufferMutuaEx* buff);
int main(){
	//chiavi
	key_t key_vett{ftok(".",TOKEN1)}, key_buff{ftok(".",TOKEN2)};
	//shmem
	int shmid_vett=shmget(key_vett,sizeof(VettoreProdCons),IPC_CREAT|0664);
	int shmid_buff=shmget(key_buff,sizeof(BufferMutuaEx),IPC_CREAT|0664);
	//attach

	VettoreProdCons* vett = (VettoreProdCons*) shmat(shmid_vett,NULL,0);

	BufferMutuaEx* buff = (BufferMutuaEx*) shmat(shmid_buff,NULL,0);
	
	//figli
	
	for(int i{0}; i<NUM_PRODUTTORI; ++i){
		pid_t pid;
		pid=fork();
		if(pid==0){
			produttore(vett);
			exit(0);
		}
	}

	for(int i{0}; i<NUM_CONSUMATORI; ++i){
		pid_t pid;
		pid=fork();
		if(pid==0){
			consumatore(vett,buff);
			exit(0);
		}
	}

	//wait figli

	int pid_ex, st;

	for(int i{0}; i<NUM_PRODUTTORI+NUM_CONSUMATORI; ++i){
		pid_ex=wait(&st);
		std::cout << pid_ex << ": terminato\n";
	}
	rimuovi_vettore(vett);
	rimuovi_buffer(buff);
	shmctl(shmid_vett,IPC_RMID,0);
	shmctl(shmid_buff,IPC_RMID,0);
	return 0;
}

void produttore(VettoreProdCons* vett){
	for(int i{0}; i<NUM_PRODUZIONI; ++i){
		printf("<%d> %d: Produco il valore: %d\n",getpid(),i,getpid());
		produci(vett,getpid());
	}
}
void consumatore(VettoreProdCons* vett, BufferMutuaEx* buff){
	for(int i{0}; i<NUM_CONSUMI; ++i){
		int valore=consuma(vett);
		aggiorna_buffer(buff,valore);
		printf("<%d> %d: Prelevato il valore: %d\n",getpid(),i,valore);
	}
}
