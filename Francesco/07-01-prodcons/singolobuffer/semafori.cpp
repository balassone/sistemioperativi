#include "semafori.h"

int Wait_Sem(int idsem, int numsem){
	int err;
	struct sembuf sem_buf;
	sem_buf.sem_num=numsem;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=-1;
	err=semop(idsem,&sem_buf,1);
	return err;
}

int Signal_Sem(int idsem, int numsem){
	int err;
	struct sembuf sem_buf;
	sem_buf.sem_num=numsem;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=1;
	err=semop(idsem,&sem_buf,1);
	return err;
}
