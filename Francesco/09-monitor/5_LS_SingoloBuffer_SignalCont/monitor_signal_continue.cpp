#include "monitor_signal_continue.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void Wait_Sem(int, int);
static void Signal_Sem(int, int);
static int Queue_Sem(int, int);

void init_monitor(Monitor* M, int numcond){
	M->mutex=semget(IPC_PRIVATE,1,IPC_CREAT|0664);
	semctl(M->mutex,0,SETVAL,1);

	M->id_conds=semget(IPC_PRIVATE,numcond,IPC_CREAT|0664);
	for(int i{0}; i<numcond; ++i){
		semctl(M->id_conds,i,SETVAL,0);
	}
	M->num_var_cond=numcond;
	M->id_shared=shmget(IPC_PRIVATE,sizeof(int)*numcond,IPC_CREAT|0664);
	M->cond_counts = (int*) shmat(M->id_shared,NULL,0);
	for(int i{0}; i<numcond; ++i){
		M->cond_counts[i]=0;
	}
}

void remove_monitor(Monitor* M){
	semctl(M->mutex,0,IPC_RMID);
	semctl(M->id_conds,0,IPC_RMID);
	shmctl(M->id_shared,IPC_RMID,0);
}

void enter_monitor(Monitor* M){
	Wait_Sem(M->mutex,0);
}

void leave_monitor(Monitor* M){
	Signal_Sem(M->mutex,0);
}

void wait_condition(Monitor* M, int cond){
	M->cond_counts[cond]=M->cond_counts[cond]+1;
	Signal_Sem(M->mutex,0);
	Wait_Sem(M->id_conds,cond);
	Wait_Sem(M->mutex,0);
}

void signal_condition(Monitor* M, int cond){
	if(M->cond_counts[cond]>0){
		M->cond_counts[cond]=M->cond_counts[cond]-1;
		Signal_Sem(M->id_conds,cond);
	}
}

int queue_condition(Monitor* M, int cond){
	return M->cond_counts[cond];
}
void Wait_Sem(int id, int num){
	struct sembuf sem_buf;
	sem_buf.sem_num=num;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=-1;
	semop(id,&sem_buf,1);
}

void Signal_Sem(int id, int num){
	struct sembuf sem_buf;
	sem_buf.sem_num=num;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=1;
	semop(id,&sem_buf,1);
}

int Queue_Sem(int id, int num){
	return (semctl(id,num,GETNCNT,NULL));
}
