#include "semafori.h"

int Wait_Sem(int desc, int num){
	int err;
	struct sembuf sem_buf;

	sem_buf.sem_num=num;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=-1;

	err = semop(desc,&sem_buf,1);
	return err;
}

int Signal_Sem(int desc, int num){
	int err;
	struct sembuf sem_buf;
	sem_buf.sem_num=num;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=1;
	err=semop(desc,&sem_buf,1);
	return err;
}
