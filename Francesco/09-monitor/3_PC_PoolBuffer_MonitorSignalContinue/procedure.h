#ifndef PROCEDURE_H
#define PROCEDURE_H
#include "monitor_signal_continue.h"
#define DIM 5

#define LIBERO 0
#define IN_USO 1
#define OCCUPATO 2

#define CV_PROD 0
#define CV_CONS 1

typedef struct{
	int buffer[DIM];
	int stato[DIM];
	
	int liberi;
	int occupati;

	Monitor m;
} ProdCons;

void Produzione(ProdCons*, int);
int Consumo(ProdCons*);

#endif //PROCEDURE_H
