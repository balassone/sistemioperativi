#include "semafori.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

int Wait_Sem(int ds_sem, int numsem){
	int err;
	struct sembuf sem_buf;
	sem_buf.sem_num=numsem;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=-1;
	err = semop(ds_sem,&sem_buf,1);
	return err;
}

int Signal_Sem(int ds_sem, int numsem){
	int err;
	struct sembuf sem_buf;
	sem_buf.sem_num=numsem;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=1;
	err = semop(ds_sem, &sem_buf, 1);
	return err;
}
