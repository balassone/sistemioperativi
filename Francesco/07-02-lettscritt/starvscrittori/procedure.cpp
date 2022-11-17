#include "semafori.h"
#include "header.h"

void InizioLettura(int sem, Buffer* buf){
	Wait_Sem(sem,MUTEXL);
	buf->numlettori=buf->numlettori+1;
	if(buf->numlettori==1) Wait_Sem(sem,SYNCH);
	Signal_Sem(sem,MUTEXL);
}

void FineLettura(int sem, Buffer* buf){
	Wait_Sem(sem,MUTEXL);
	buf->numlettori=buf->numlettori-1;
	if(buf->numlettori==0) Signal_Sem(sem, SYNCH);
	Signal_Sem(sem,MUTEXL);
}

void InizioScrittura(int sem){
	Wait_Sem(sem,SYNCH);
}

void FineScrittura(int sem){
	Signal_Sem(sem,SYNCH);
}
