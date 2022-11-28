#include "procedure.h"
#include <unistd.h>

void Produzione(ProdCons* pc, int val){
	enter_monitor(&(pc->m));
	while(pc->liberi==0){
		wait_condition(&(pc->m),CV_PROD);
	}

	int i=0;
	while(i<DIM && pc->stato[i]!=LIBERO){
		i++;
	}
	pc->liberi=pc->liberi-1;
	pc->stato[i]=IN_USO;
	
	leave_monitor(&(pc->m));
	sleep(2);
	pc->buffer[i]=val;
	
	enter_monitor(&(pc->m));
	
	pc->stato[i]=OCCUPATO;
	pc->occupati=pc->occupati+1;

	signal_condition(&(pc->m),CV_CONS);
	leave_monitor(&(pc->m));
}

int Consumo(ProdCons* pc){
	enter_monitor(&(pc->m));
	while(pc->occupati==0){
		wait_condition(&(pc->m),CV_CONS);
	}

	int i=0;
	while(i<DIM && pc->stato[i]!=OCCUPATO) i++;

	pc->stato[i]=IN_USO;
	pc->occupati=pc->occupati-1;
	leave_monitor(&(pc->m));

	sleep(2);
	int val=pc->buffer[i];

	enter_monitor(&(pc->m));
	pc->stato[i]=LIBERO;
	pc->liberi=pc->liberi+1;
	signal_condition(&(pc->m),CV_PROD);
	leave_monitor(&(pc->m));
	return val;
}
