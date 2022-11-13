#include <iostream>
#include "procedure.h"
#include "semafori.h"
#include <time.h>
#include <unistd.h>
void produttore(struct prodcons* p, int ds_sem){
	Wait_Sem(ds_sem,SPAZIO_DISP);
	Wait_Sem(ds_sem, MUTEXP);
	int i=0;
	while(i<DIM_BUFFER && p->stato[i]!=BUFFER_VUOTO){
		i++;
	}
	p->stato[i]=BUFFER_INUSO;
	Signal_Sem(ds_sem,MUTEXP);
	sleep(2);
	p->buffer[i]=rand()%100;
	p->stato[i]=BUFFER_PIENO;
	Signal_Sem(ds_sem,NUM_MESSAGGI);
}

void consumatore(struct prodcons* p, int ds_sem){
	Wait_Sem(ds_sem, NUM_MESSAGGI);
	Wait_Sem(ds_sem, MUTEXC);
	int i=0;
	while(i<DIM_BUFFER && p->stato[i]!=BUFFER_PIENO){
		i++;
	}
	p->stato[i]=BUFFER_INUSO;
	Signal_Sem(ds_sem,MUTEXC);
	sleep(2);
	std::cout << "Il valore consumato e': " << p->buffer[i] << std::endl;
	p->stato[i]=BUFFER_VUOTO;
	Signal_Sem(ds_sem,SPAZIO_DISP);
}
