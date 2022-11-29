#include "procedure.h"

void Scrittura(LettScritt* ls, int val){
	enter_monitor(&(ls->m));

	while(ls->numlettori>0 || ls->numscrittori>0){
		wait_condition(&(ls->m),CV_SCRITT);
	}

	ls->numscrittori=ls->numscrittori+1;
	leave_monitor(&(ls->m));

	ls->buf=val;

	enter_monitor(&(ls->m));
	ls->numscrittori=ls->numscrittori-1;

	if(queue_condition(&(ls->m),CV_SCRITT)) signal_condition(&(ls->m),CV_SCRITT);
	else signal_condition(&(ls->m),CV_LETT);

	leave_monitor(&(ls->m));
}

int Lettura(LettScritt* ls){
	enter_monitor(&(ls->m));
	while(ls->numscrittori>0) wait_condition(&(ls->m),CV_LETT);
	ls->numlettori=ls->numlettori+1;
	signal_condition(&(ls->m),CV_LETT);

	leave_monitor(&(ls->m));

	int val = ls->buf;

	enter_monitor(&(ls->m));
	ls->numlettori=ls->numlettori-1;
	if(ls->numlettori==0) signal_condition(&(ls->m),CV_SCRITT);

	leave_monitor(&(ls->m));
	return val;
}
