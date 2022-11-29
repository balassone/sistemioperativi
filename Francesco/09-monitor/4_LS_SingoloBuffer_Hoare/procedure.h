#ifndef PROCEDURE_H
#define PROCEDURE_H
#include "monitor_hoare.h"
#define CV_LETT 0
#define CV_SCRITT 1

#define NUM_VAR_COND 2

typedef struct{
	int buffer;

	int numlettori;
	int numscrittori;

	Monitor m;

} LettScritt;

int Lettura(LettScritt*);
void Scrittura(LettScritt*, int);

#endif
