#include <stdio.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "header.h"
#include <iostream>
#include <time.h>
void Produci(ProdCons* pc, msg m){
	InizioProduzione(pc);

	pc->mess = m;


	std::cout << "Valore PRODOTTO = [" << m << "]\n";
	FineProduzione(pc);
}

msg Consuma(ProdCons* pc){
	InizioConsumo(pc);

	msg mess=pc->mess;

	std::cout << "Valore CONSUMATO = [" << mess << "]\n";
	FineConsumo(pc);
	return mess;
}

void InizioConsumo(ProdCons* pc){
	pthread_mutex_lock(&pc->mutex);
	while(pc->ok_consumo==0){
		pthread_cond_wait(&pc->ok_cons_cv,&pc->mutex);
	}
}

void FineConsumo(ProdCons* pc){
	pc->ok_produzione=1;
	pc->ok_consumo=0;
	pthread_cond_signal(&pc->ok_prod_cv);
	pthread_mutex_unlock(&pc->mutex);
}

void InizioProduzione(ProdCons* pc){
	pthread_mutex_lock(&pc->mutex);
	while(pc->ok_produzione==0){
		pthread_cond_wait(&pc->ok_prod_cv,&pc->mutex);
	}
}

void FineProduzione(ProdCons* pc){
	pc->ok_produzione=0;
	pc->ok_consumo=1;
	pthread_cond_signal(&pc->ok_cons_cv);
	pthread_mutex_unlock(&pc->mutex);
}

void* Produttore (void* p){
	ProdCons* pc = (ProdCons*) p;
	srand(time(NULL));
	for(int i{0}; i<3; ++i){
		msg mess = rand()%100 + 1;
		Produci(pc,mess);
	}
	pthread_exit(NULL);
}

void* Consumatore(void* p){
	ProdCons* pc=(ProdCons*) p;
	for(int i{0}; i<3; ++i){
		msg mess = Consuma(pc);
	}
	pthread_exit(NULL);
}
