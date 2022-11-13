#ifndef PROCEDURE_H
#define PROCEDURE_H
#define SPAZIO_DISPONIBILE 0
#define NUM_MESSAGGI 1
#define MUTEXC 2
#define MUTEXP 3
#define DIM_BUFFER 3

#define NUMPRODUTTORI 5
#define NUMCONSUMATORI 5

struct prodcons{
	int buffer[DIM_BUFFER];
	int testa;
	int coda;
};

void produttore(struct prodcons*, int);
void consumatore(struct prodcons*, int);

#endif
