			/*----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER

#define SIZE 4

#define LIBERO 0
#define IN_USO 1
#define OCCUPATO 2

#define NPROD 3
#define NCONS 3

typedef struct{
	int chiave;
	int valore;
} ElemBuffer;

typedef struct{
	ElemBuffer elementi[SIZE];
	int stati[SIZE];
} BufferCircolare;

//INSERIRE IDENTIFICATIVI SEMAFORI
#define SPAZIO_DISP 0
#define MSG_DISP_1 1
#define MSG_DISP_2 2
#define MSG_DISP_3 3
#define MUTEXC 4
#define MUTEXP 5

//Nota Studente: ho scelto gli indici dei semafori uguali al valore della chiave, così che nelle funzioni posso usare il valore della chiave anche come valore dell'indice.

void Wait_Sem(int, int);
void Signal_Sem (int, int);

void produci(BufferCircolare* buf, int chiave, int semid);
void consuma(BufferCircolare* buf, int chiave, int semid);

#endif
