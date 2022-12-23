			/*----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER

#define N 5

typedef struct{
	int elementi[N];
	int testa;
	int coda;
} BufferCircolare;

//INSERIRE VARIABILI CHE SERVONO
#define SPAZIO_DISP 0
#define NUM_MESS 1
#define MUTEXP 2

#define PATH_SHM "."
#define CHAR_SHM 'a'
#define PATH_SEM "."
#define CHAR_SEM 'b'

void Wait_Sem(int, int, int);
void Signal_Sem (int, int, int);

void produci_elemento(int semid,BufferCircolare* buf);
void consuma_elementi(int semid, BufferCircolare* buf);

#endif
