#include <iostream>
#include "semafori.h"
#include "procedure.h"
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

using std::cout;
using std::endl;

int main(){
	key_t teatro_key=ftok(".",'a');
	key_t disp_key=IPC_PRIVATE;
	key_t sem_key=ftok(".",'b');
	int ds_teatro=shmget(teatro_key,sizeof(teatro),IPC_CREAT|0664);
	teatro* t = (teatro*) shmat(ds_teatro,NULL,0);
	for(int i{0}; i<CAPIENZA; ++i){
		t[i]->stato=LIBERO;
		t[i]->id_cliente=0;
	}
	int ds_disp=shmget(disp_key,sizeof(int),IPC_CREAT|0664);
	int* disp=(int*)shmat(ds_disp,NULL,0);
	*disp=CAPIENZA;
	int ds_sem=semget(sem_key,4,IPC_CREAT|0664);
	semctl(ds_sem,SPAZIO_DISP,SETVAL,CAPIENZA);
	semctl(ds_sem,NUM_MESS,SETVAL,0);
	semctl(ds_sem,MUTEX_DISP,SETVAL,1);
	semctl(ds_sem,MUTEX_TEATRO,SETVAL,1);

	
	return 0;
}
