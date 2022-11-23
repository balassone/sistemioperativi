#include "monitor_hoare.h"
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>

static void Wait_Sem(int, int);
static void Signal_Sem(int, int);
static int Queue_Sem(int, int);

void init_monitor(Monitor* M, int num_var){
	
	// Inizializzo Mutex
	M->mutex=semget(IPC_PRIVATE,1,IPC_CREAT|0664);
	semctl(M->mutex,0,SETVAL,1);
	
	// Inizializzo Urgent
	M->urgent_sem=semget(IPC_PRIVATE,1,IPC_CREAT|0664);
	semctl(M->urgent_sem,0,SETVAL,0);
	
	// Inizializzo Semafori Condition
	M->id_conds=semget(IPC_PRIVATE,num_var,IPC_CREAT|0664);
	for(int i{0}; i<num_var; ++i) semctl(M->id_conds,i,SETVAL,0);
	
	// Inizializzo Shmem + Attach + Inizializzo counts
	M->id_shared=shmget(IPC_PRIVATE,sizeof(int)*(num_var+1),IPC_CREAT|0664);
	M->cond_counts = (int*) shmat(M->id_shared,NULL,0);
	for(int i{0}; i<num_var; ++i) M->cond_counts[i]=0;

	// Inizializzo num var cond
	M->num_var_cond=num_var;
	
	// Assegno l'indirizzo corretto a urgent_count
	M->urgent_count = M->cond_counts + M->num_var_cond;

	//Inizializzo urgent count
	*(M->urgent_count)=0;

#ifdef DEBUG
	printf("Monitor inizializzato con %d variabili condition!\n", num_var);
#endif

}


void enter_monitor(Monitor* M){
#ifdef DEBUG
	printf("<%d> Tenta di entrare nel monitor\n",getpid());
#endif
	Wait_Sem(M->mutex,0);
#ifdef DEBUG
	printf("<%d> Entrato con successo nel monitor\n",getpid());
#endif
}


void leave_monitor(Monitor* M){
#ifdef DEBUG
	printf("<%d> Uscito dal Monitor\n",getpid());
#endif
	if(*(M->urgent_count)>0){
#ifdef DEBUG
		printf("<%d> Segnala sulla coda Urgent!\n", getpid());
#endif
		Signal_Sem(M->urgent_sem,0);
	} else {
#ifdef DEBUG
		printf("<%d> Nessuno in Urgent, Segnala sul Mutex\n",getpid());
#endif
		Signal_Sem(M->mutex,0);
	}
}


void remove_monitor(Monitor* M){
	semctl(M->mutex,0,IPC_RMID);
	semctl(M->urgent_sem,0,IPC_RMID);
	semctl(M->id_conds,M->num_var_cond, IPC_RMID);
	shmctl(M->id_shared,IPC_RMID,0);
#ifdef DEBUG
	printf("\n Il monitor e' stato rimosso! Addio!!\n");
#endif
}

void wait_condition(Monitor* M, int id_var){
#ifdef DEBUG
	if(id_var<0 || id_var>M->num_var_cond) printf("<%d> Errore nell'invocazione della wait\n", getpid());
#endif

#ifdef DEBUG
	printf("<%d> Invocata la wait sulla variabile condition %d\n",getpid(), id_var);
#endif
	M->cond_counts[id_var]=M->cond_counts[id_var]+1;
	if(*(M->urgent_count)>0){
#ifdef DEBUG
		printf("<%d> Monitor signal sulla urgent\n",getpid());
#endif
		Signal_Sem(M->urgent_sem,0);
	} else {
#ifdef DEBUG
		printf("<%d> Monitor signal sul mutex\n", getpid());
#endif
		Signal_Sem(M->mutex,0);
	}
	Wait_Sem(M->id_conds,id_var);
	M->cond_counts[id_var]=M->cond_counts[id_var]-1; //Lo faccio qui perché è Signal and Wait e ci vuole if
}

void signal_condition(Monitor* M, int id_var){
#ifdef DEBUG
	if(id_var<0 || id_var>M->num_var_cond) printf("<%d> Errore nell'invocazione della signal\n",getpid());
#endif

#ifdef DEBUG
	printf("<%d> Invocata la signal sulla variabile condition %d\n",getpid(), id_var);
#endif
	(*(M->urgent_count))++;
	if(M->cond_counts[id_var]>0){
		Signal_Sem(M->id_conds, id_var);
#ifdef DEBUG
		printf("<%d> Invocata la signal sul numero %d\n",getpid(),id_var);
#endif
#ifdef DEBUG
		printf("<%d> Processo segnalante si mette in urgent wait\n",getpid());
#endif

		Wait_Sem(M->urgent_sem,0);
#ifdef DEBUG
		printf("<%d> Processo uscito dalla coda urgent\n",getpid());
#endif
	}
	(*(M->urgent_count))--;
}


int queue_condition(Monitor* M, int id_var){
	return M->cond_counts[id_var];
}

void Wait_Sem(int id_sem, int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num=numsem;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=-1;
	semop(id_sem,&sem_buf,1);
}

void Signal_Sem(int id_sem, int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num=numsem;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=1;
	semop(id_sem,&sem_buf,1);
}

int Queue_Sem(int id_sem, int numsem){
	return((semctl(id_sem,numsem,GETNCNT,NULL)));
}

