#ifndef PROCEDURE_H
#define PROCEDURE_H

#define CAPIENZA 80

#define SPAZIO_DISP 0
#define NUM_MESS 1
#define MUTEX_DISP 2
#define MUTEX_TEATRO 3

#define LIBERO 0
#define OCCUPATO 1
#define AGGIORNAMENTO 2


/*
Wait(Num_Mess)
Stampa Teatro
Signal(Spazio_Disp)
*/

/*
Wait(Spazio_Disp)
sleep
num%5
Wait(MUTEXDISP)
if...
Signal(MUTEXDISP)
for ...
Wait(MutexTea)
...
Signal(MutexTea)
Signal(Num_Mess)
*/

typedef struct{
	unsigned int id_cliente;
	unsigned int stato;
} posto;

typedef posto teatro[CAPIENZA];

void cliente(teatro*, int*, int);
void visualizzatore(teatro*, int);
#endif
