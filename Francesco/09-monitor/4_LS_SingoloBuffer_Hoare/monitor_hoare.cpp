#include "monitor_hoare.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/shm.h>

static void Wait_Sem(int, int);
static void Signal_Sem(int, int);
static int Queue_Sem(int, int);

void init_monitor(Monitor* M, int num_cond){
	
	// Mutex
	M->mutex=semget(IPC_PRIVATE,1,IPC_CREAT|0664);
	semctl(M->mutex,0,SETVAL,1);

	// Urgent
	M->urgent_sem=semget(IPC_PRIVATE,1,IPC_CREAT|0664);
	semctl(M->urgent_sem,0,SETVAL,0);

	// Conds
	M->id_conds=semget(IPC_PRIVATE,num_cond,IPC_CREAT|0664);
	for(int i{0}; i<num_cond; ++i){
		semctl(M->id_conds,i,SETVAL,0);
	}

	// SHM
	M->id_shared=shmget(IPC_PRIVATE,sizeof(int)*(1+num_cond),IPC_CREAT|0664);
	M->cond_counts=(int*) shmat(M->id_shared,NULL,0);
	M->num_var_cond=num_cond;
	M->urgent_count=M->cond_counts+M->num_var_cond;
	for(int i{0}; i<num_cond; ++i){
		M->cond_counts[i]=0;
	}
	*(M->urgent_count)=0;
}

void enter_monitor(Monitor* M){
	Wait_Sem(M->mutex,0);
}

void leave_monitor(Monitor* M){
	if(*(M->urgent_count)>0){
		Signal_Sem(M->urgent_sem,0);
	} else {
		Signal_Sem(M->mutex,0);
	}
}

void remove_monitor(Monitor* M){
	semctl(M->mutex,0,IPC_RMID);
	semctl(M->urgent_sem,0,IPC_RMID);
	semctl(M->id_conds,0,IPC_RMID);
	shmctl(M->id_shared,IPC_RMID,0);
}

void wait_condition(Monitor* M, int cond){
	M->cond_counts[cond]=M->cond_counts[cond]+1;
	if(*(M->urgent_count)>0){
		Signal_Sem(M->urgent_sem,0);
	} else {
		Signal_Sem(M->mutex,0);
	}
	Wait_Sem(M->id_conds,cond);
	M->cond_counts[cond]=M->cond_counts[cond]-1;
}

void signal_condition(Monitor* M, int cond){
	*(M->urgent_count)++;
	if(M->cond_counts[cond]>0){
		Signal_Sem(M->id_conds,cond);
		Wait_Sem(M->urgent_sem,0);
	}
	*(M->urgent_count)--;
}

int queue_condition(Monitor* M, int cond){
	return M->cond_counts[cond];
}
void Wait_Sem(int semid, int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num=numsem;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=-1;
	semop(semid,&sem_buf,1);
}

void Signal_Sem(int semid, int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num=numsem;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=1;
	semop(semid,&sem_buf,1);
}

int Queue_Sem(int semid, int numsem){
	return(semctl(semid,numsem,GETNCNT,NULL));
}
