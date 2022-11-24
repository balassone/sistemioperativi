#include "procedure.h"

void produci(ProdCons* pc, int val){
	enter_monitor(&(pc->m));
	while(pc->buffer_pieno==1){
		wait_condition(&(pc->m),CV_PROD);
	}

	pc->buffer=val;
	pc->buffer_pieno=1;
	pc->buffer_vuoto=0;

	signal_condition(&(pc->m),CV_CONS);

	leave_monitor(&(pc->m));
}

int consuma(ProdCons* pc){
	enter_monitor(&(pc->m));
	while(pc->buffer_vuoto==1){
		wait_condition(&(pc->m),CV_CONS);
	}

	int val = pc->buffer;
	pc->buffer_vuoto=1;
	pc->buffer_pieno=0;
	signal_condition(&(pc->m),CV_PROD);
	leave_monitor(&(pc->m));
	return val;
}
