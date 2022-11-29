#include "procedure.h"
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

using std::cout;
using std::endl;

int main(){
	key_t shm_key=IPC_PRIVATE;
	int ds_shm=shmget(shm_key,sizeof(LettScritt),IPC_CREAT|0664);
	LettScritt* ls = (LettScritt*) shmat(ds_shm,NULL,0);

	ls->buf=0;
	ls->numlettori=0;
	ls->numscrittori=0;

	init_monitor(&(ls->m),2);

	pid_t pid;

	for(int i{0}; i<3; ++i){
		pid=fork();
		if(pid==0){
			srand(getpid()*time(NULL));
			
			int val=rand()%100+1;

			Scrittura(ls,val);

			cout << getpid() << ": Scrivo " << val << " nel buffer\n";

			exit(0);
		}
	}
	
	for(int i{0}; i<3; ++i){
		pid=fork();
		if(pid==0){
			cout << getpid() << ": Leggo " << Lettura(ls) << " dal buffer\n";
			exit(0);
		}
	}
	for(int i{0}; i<6; ++i) wait(NULL);
	remove_monitor(&(ls->m));

	shmctl(ds_shm,IPC_RMID,0);
	return 0;
}
