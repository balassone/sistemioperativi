#include "header.h"
#include <stdio.h>
#include <unistd.h>
void inizioLettura(LettScritt* ls, int semid){
	Wait_Sem(semid,MUTEXL);
	ls->numlettori=ls->numlettori+1;
	if(ls->numlettori==1) Wait_Sem(semid,SYNCH);
	Signal_Sem(semid,MUTEXL);
}

void fineLettura(LettScritt* ls, int semid){
	Wait_Sem(semid,MUTEXL);
	ls->numlettori=ls->numlettori-1;
	if(ls->numlettori==0) Signal_Sem(semid,SYNCH);
	Signal_Sem(semid,MUTEXL);
}

void inizioScrittura(LettScritt* ls, int semid){
	Wait_Sem(semid,MUTEXS);
	ls->numscrittori=ls->numscrittori+1;
	if(ls->numscrittori==1) Wait_Sem(semid,SYNCH);
	Signal_Sem(semid,MUTEXS);
	Wait_Sem(semid,MUTEX);
}

void fineScrittura(LettScritt* ls, int semid){
	Signal_Sem(semid,MUTEX);
	Wait_Sem(semid,MUTEXS);
	ls->numscrittori=ls->numscrittori-1;
	if(ls->numscrittori==0) Signal_Sem(semid,SYNCH);
	Signal_Sem(semid,MUTEXS);
}

void Scrittore(LettScritt* ls, int semid, int val){
	inizioScrittura(ls,semid);
	ls->buffer=val;
	printf("Scrittore scrive %d\n",val);
	fineScrittura(ls,semid);
}

int Lettore(LettScritt* ls, int semid){
	inizioLettura(ls,semid);
	int val=ls->buffer;
	printf("Lettore legge %d\n",val);
	fineLettura(ls,semid);
	return val;
}
