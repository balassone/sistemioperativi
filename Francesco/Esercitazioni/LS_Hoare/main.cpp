#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>
#define N 6
#include "header.h"
int main(){

	int shm = shmget(IPC_PRIVATE,sizeof(LettScritt),IPC_CREAT|0664);
	LettScritt* ls = (LettScritt*) shmat(shm,NULL,0);

	ls->buffer=0;
	ls->numlettori=0;
	ls->numscrittori=0;
	init_monitor(&(ls->m),2);

	for(int i=0; i<N; ++i){
		int pid;
		if(i%2){
			pid=fork();
			if(pid==0){
				srand(getpid());
				int val=rand()%100;
				Scrivi(ls,val);
				exit(0);
			}
		} else {
			pid=fork();
			if(pid==0){
				Leggi(ls);
				exit(0);
			}
			
		}
	}

	for(int i=0; i<N; ++i) wait(NULL);
	remove_monitor(&(ls->m));
	shmctl(shm,IPC_RMID,NULL);
	return 0;
}
