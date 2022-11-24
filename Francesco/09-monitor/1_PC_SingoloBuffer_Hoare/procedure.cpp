#include "procedure.h"

void Produci(ProdCons* pc, int val){
	enter_monitor(&pc->m);
	if(pc->buffer_occupato==1){
		wait_condition(&pc->m,CV_PRODUTTORI);
	}
	pc->buffer=val;
	pc->buffer_libero=0;
	pc->buffer_occupato=1;
	signal_condition(&pc->m,CV_CONSUMATORI);
	leave_monitor(&pc->m);
}

int Consuma(ProdCons* pc){
	enter_monitor(&pc->m);
	if(pc->buffer_libero==1){
		wait_condition(&pc->m,CV_CONSUMATORI);
	}
	int val = pc->buffer;
	pc->buffer_libero=1;
	pc->buffer_occupato=0;
	signal_condition(&pc->m,CV_PRODUTTORI);
	leave_monitor(&pc->m);
	return val;
}
