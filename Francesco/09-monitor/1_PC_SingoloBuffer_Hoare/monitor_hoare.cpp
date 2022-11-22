#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include "monitor_hoare.h"

static void Wait_Sem(int, int);
static void Signal_Sem(int, int);
static int Queue_Sem(int, int);

void init_monitor(Monitor* M, int num_var){
	M->mutex=semget(IPC_PRIVATE,1,IPC_CREAT|0664);
	semctl(M->mutex,0,SETVAL,1);
	M->id_cons=semget(IPC_PRIVATE,num_var,IPC_CREAT|0664);
	for(int i{0}; i<num_var; ++i){
		semctl(M->id_cons,i,SETVAL,0);
	}
	M->id_shared=shmget(IPC_CREAT,sizeof(int)*(num_var+1),IPC_CREAT|0664);
	M->cond_counts=(int*) shmat(M->id_shared,NULL,0);
	M->num_var_cond=num_var;
	M->urgent_count=M->cond_counts+M->num_var_cond;
	for(int i{0}; i<num_var; ++i){
		M->cond_counts[i]=0;
	}
	*(M->urgent_count)=0;
#ifdef DEBUG_
	printf("Monitor inizializzato con %d variabili condition.",num_var);
#endif
}
