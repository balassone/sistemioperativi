#ifndef HEADER_H
#define HEADER_H
#include "monitor_hoare.h"
#define CV_PRODUTTORI 0
#define CV_CONSUMATORI 1
typedef struct{
	Monitor m;
	int buffer;
	int buffer_libero;
	int buffer_occupato;
} ProdCons;

void Produci(ProdCons*, int);
int Consuma(ProdCons*);

#endif //HEADER_H
