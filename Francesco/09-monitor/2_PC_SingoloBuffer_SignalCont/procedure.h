#ifndef PROCEDURE_H
#define PROCEDURE_H
#include "monitor_signal_continue.h"
#define CV_PROD 0
#define CV_CONS 1

typedef struct{
	int buffer;
	
	int buffer_vuoto;
	int buffer_pieno;

	Monitor m;
} ProdCons;

void produci(ProdCons*, int);
int consuma(ProdCons*);

#endif
