#include "semafori.h"
#include "procedure.h"

void InizioLettura(int sem, Buffer* buf){
	Wait_Sem(sem,MUTEXL);
	buf->numlettori=buf->numlettori+1;
	if(buf->numlettori==1) Wait_Sem(sem,SYNCH);
	Signal_Sem(sem,MUTEXL);
}

void FineLettura(int sem, Buffer* buf){
	Wait_Sem(sem,MUTEXL);
	buf->numlettori=buf->numlettori-1;
	if(buf->numlettori==0) Signal_Sem(sem,SYNCH);
	Signal_Sem(sem,MUTEXL);
}

void InizioScrittura(int sem, Buffer* buf){
	Wait_Sem(sem,MUTEXS);
	buf->numscrittori=buf->numscrittori+1;
	if(buf->numscrittori==1) Wait_Sem(sem, SYNCH);
	Signal_Sem(sem, MUTEXS);
	Wait_Sem(sem,MUTEX);
}

void FineScrittura(int sem, Buffer* buf){
	Signal_Sem(sem,MUTEX);
	Wait_Sem(sem,MUTEXS);
	buf->numscrittori=buf->numscrittori-1;
	if(buf->numscrittori==0) Signal_Sem(sem, SYNCH);
	Signal_Sem(sem,MUTEXS);
}
