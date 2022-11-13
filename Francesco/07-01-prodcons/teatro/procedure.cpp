#include "procedure.h"
#include "semafori.h"
#include <iostream>
#include <unistd.h>
#include <time.h>
void cliente(teatro* t, int* disp, int ds_sem){
	Wait_Sem(ds_sem,SPAZIO_DISP);
	sleep(rand()%5+1);
	int num=rand()%4+1;
	Wait_Sem(ds_sem,MUTEX_DISP);
	if(num<=(*disp)){
		int tmp=(*disp);
		*disp=tmp-num;
		Signal_Sem(ds_sem,MUTEX_DISP);
		for(int i{0}; i<num; ++i){
			Wait_Sem(ds_sem,MUTEX_TEATRO);
			int j{0};
			while(j<CAPIENZA && t[j]->stato!=LIBERO){
				j++;
			}
			t[j]->stato=AGGIORNAMENTO;
			Signal_Sem(ds_sem,MUTEX_TEATRO);
			sleep(1);
			t[j]->id_cliente=getpid();
			t[j]->stato=OCCUPATO;
		}
	} else{
		std::cout << "disponibilita' esaurita\n";
		Signal_Sem(ds_sem,MUTEX_DISP);
	}
	Signal_Sem(ds_sem,NUM_MESS);
}

void visualizzatore(teatro* t, int ds_sem){
	Wait_Sem(ds_sem,NUM_MESS);
	Wait_Sem(ds_sem,MUTEX_TEATRO);
	for(int i{0}; i<CAPIENZA; ++i){
		std::cout << "Posto " << i << ": ";
		if(t[i]->stato==LIBERO) std::cout << "LIBERO.\n";
		if(t[i]->stato==AGGIORNAMENTO) std::cout << "AGGIORNAMENTO.\n";
		if(t[i]->stato==OCCUPATO) std::cout << "OCCUPATO DA " << t[i]->id_cliente << std::endl;
		std::cout << std::endl;
	}
	Signal_Sem(ds_sem,MUTEX_TEATRO);
	Signal_Sem(ds_sem,SPAZIO_DISP);
}
