			/*----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER

#define N 5

typedef struct{
	int elementi[N];
	int testa;
	int coda;
	int semid;
} BufferCircolare;

//INSERIRE VARIABILI CHE SERVONO

#define SPAZIO_DISP 0
#define NUM_MESS 1
#define MUTEXP 2
#define FTOK_PATH_Q "."
#define FTOK_CHAR_Q '.'

void Wait_Sem(int, int);
void Signal_Sem (int, int);

void produci_elemento(int semid,BufferCircolare* buf);
void consuma_elementi(int semid, BufferCircolare* buf);

#endif
