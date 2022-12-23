#include <iostream>
#include "header.h"
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main(){
	int semid=semget(IPC_PRIVATE,4,IPC_CREAT|0664);
	int shmid=shmget(IPC_PRIVATE,sizeof(LettScritt),IPC_CREAT|0664);

	for(int i=0; i<4; ++i){
		semctl(semid,i,SETVAL,1);
	}

	LettScritt* ls = (LettScritt*) shmat(shmid,NULL,0);
	ls->buffer=0;
	ls->numlettori=0;
	ls->numscrittori=0;

	for(int i=0; i<20; ++i){
		if(i%2==0){
			int pid=fork();
			if(pid==0){
				srand(getpid());
				int val=rand()%100;
				Scrittore(ls,semid,val);
				exit(0);
			}
		} else{
			int pid=fork();
			if(pid==0){
				int val=Lettore(ls,semid);
				exit(0);
			}
		}
	}
	for(int i=0; i<20; ++i) wait(NULL);

	semctl(semid,0,IPC_RMID);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
