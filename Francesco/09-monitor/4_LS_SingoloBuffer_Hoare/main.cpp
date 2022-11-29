#include "procedure.h"
#include <iostream>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <time.h>

#define N 3

int main(){
	key_t shm_key = IPC_PRIVATE;
	int shmid = shmget(shm_key,sizeof(LettScritt),IPC_CREAT|0664);
	LettScritt* ls = (LettScritt*) shmat(shmid,NULL,0);
	init_monitor(&(ls->m),2);

	for(int i{0}; i<N; ++i){
		pid_t pid=fork();
		if(pid==0){
			std::cout << "Lettore " << i << " legge: " << Lettura(ls) << std::endl;
			exit(0);
		}
	}

	for(int i{0}; i<N; ++i){
		pid_t pid=fork();
		if(pid==0){
			srand(getpid()*time(NULL));
			int val=rand()%100 +1;
			Scrittura(ls,val);
			std::cout << "Scrittore " << i << " scrive: " << val << std::endl;
			exit(0);
		}
	}

	for(int i=0; i<(N+N); ++i) wait(NULL);

	remove_monitor(&(ls->m));
	shmctl(shmid,IPC_RMID,0);
	return 0;
}
