			/*----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER

#include "semafori.h"

#define DIM 4

// TODO: definire semafori
/*Definisco due tipi di messaggio disponibile,
inutile segnalare consumatori il cui messaggio non è stato prodotto
*/

#define SPAZIO_DISP 0 //Inizializzare a DIM
#define MSG1_DISP 1 //Inizializzare a 0
#define MSG2_DISP 2 //Inizializzare a 0
#define MUTEXC 3 //Inizializzare a 1
#define MUTEXP 4 //Inizializzare a 1

#define LIBERO 0
#define IN_USO 1
#define OCC_TIPO1 2
#define OCC_TIPO2 3

#define NPROD 4
#define NCONS 2

#define PRODS 4
#define CONS 8

typedef struct {
	
	// TODO: completare campi struct
	int buffer[DIM];
	int stato[DIM]; //Inizializza a libero

} BufferMutuaEx;

void produci_tipo_1(BufferMutuaEx * buf, int semid, int val);
void produci_tipo_2(BufferMutuaEx * buf, int semid, int val);
void consuma_tipo_1(BufferMutuaEx * buf, int semid);
void consuma_tipo_2(BufferMutuaEx * buf, int semid);



#endif
