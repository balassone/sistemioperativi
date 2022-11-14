#include "header.h"

void Inizio_Lettura(int sem, Buffer* buf){
	Wait_Sem(sem,MUTEXL);
	buf->numlettori=buf->numlettori+1;
	if(buf->numlettori==1) Wait_Sem(sem,SYNCH);
	Signal_Sem(sem,MUTEXL);
}

void Fine_Lettura(int sem, Buffer* buf){
	Wait_Sem(sem,MUTEXL);
	buf->numlettori=buf->numlettori-1;
	if(buf->numlettori==0) Signal_Sem(sem,SYNCH);
	Signal_Sem(sem,MUTEXL);
}

void Inizio_Scrittura(int sem){
	Wait_Sem(sem,SYNCH);
}

void Fine_Scrittura(int sem){
	Signal_Sem(sem,SYNCH);
}
