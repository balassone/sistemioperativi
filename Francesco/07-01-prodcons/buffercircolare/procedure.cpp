#include "procedure.h"
#include "semafori.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
void produttore(struct prodcons* pc, int sem){
	Wait_Sem(sem, SPAZIO_DISPONIBILE);
	Wait_Sem(sem, MUTEXP);
	sleep(2);
	pc->buffer[pc->testa]=rand()%100;
	pc->testa=(pc->testa+1)%DIM_BUFFER;
	Signal_Sem(sem, MUTEXP);
	Signal_Sem(sem, NUM_MESSAGGI);
}

void consumatore(struct prodcons* pc, int sem){
	Wait_Sem(sem,NUM_MESSAGGI);
	Wait_Sem(sem,MUTEXC);
	sleep(2);
	std::cout << "Messaggio Letto: " << pc->buffer[pc->coda] << std::endl;
	pc->coda=(pc->coda+1)%DIM_BUFFER;
	Signal_Sem(sem,MUTEXC);
	Signal_Sem(sem, SPAZIO_DISPONIBILE);
}
