#include "header.h"
#include <unistd.h>
#include <stdio.h>
void inizioLettura(LettScritt* ls){
	enter_monitor(&(ls->m));
	if(ls->numscrittori>0){
		wait_condition(&(ls->m),CV_LETT);
	}
	ls->numlettori=ls->numlettori+1;
	signal_condition(&(ls->m),CV_LETT);
	leave_monitor(&(ls->m));
}

void fineLettura(LettScritt* ls){
	enter_monitor(&(ls->m));
	ls->numlettori=ls->numlettori-1;
	if(ls->numlettori==0) signal_condition(&(ls->m),CV_SCRITT);
	leave_monitor(&(ls->m));
}

void inizioScrittura(LettScritt* ls){
	enter_monitor(&(ls->m));
	if(ls->numlettori>0 || ls->numscrittori>0){
		wait_condition(&(ls->m),CV_SCRITT);
	}
	ls->numscrittori=ls->numscrittori+1;
	leave_monitor(&(ls->m));
}

void fineScrittura(LettScritt* ls){
	enter_monitor(&(ls->m));
	ls->numscrittori=ls->numscrittori-1;
	if(queue_condition(&(ls->m),CV_SCRITT)) signal_condition(&(ls->m),CV_SCRITT);
	else signal_condition(&(ls->m),CV_LETT);
	leave_monitor(&(ls->m));
}

void Scrivi(LettScritt* ls, int val){
	inizioScrittura(ls);
	printf("[%d] Scrivo il valore: %d\n",getpid(),val);
	ls->buffer=val;
	fineScrittura(ls);
}

int Leggi(LettScritt* ls){
	inizioLettura(ls);
	int val=ls->buffer;
	printf("[%d] Leggo il valore: %d\n",getpid(),val);
	fineLettura(ls);
	return val;
}
