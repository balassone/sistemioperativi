#ifndef PROCEDURE_H
#define PROCEDURE_H
#define NUM_MESSAGGI 0
#define SPAZIO_DISP 1
#define MUTEXP 2
#define MUTEXC 3
#define DIM_BUFFER 5
#define NUMPRODUTTORI 6
#define NUMCONSUMATORI 6

#define BUFFER_VUOTO 0
#define BUFFER_PIENO 1
#define BUFFER_INUSO 2

struct prodcons{
	int buffer[DIM_BUFFER];
	int stato[DIM_BUFFER];
};

void produttore(struct prodcons*, int ds_sem);
void consumatore(struct prodcons*, int ds_sem);

#endif
