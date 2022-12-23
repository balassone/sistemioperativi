#ifndef HEADER_H
#define HEADER_H
#include "monitor_hoare.h"
#define CV_LETT 0
#define CV_SCRITT 1

typedef struct{

	int buffer;
	int numlettori;
	int numscrittori;

	Monitor m;

} LettScritt;

void inizioLettura(LettScritt*);
void fineLettura(LettScritt*);
void inizioScrittura(LettScritt*);
void fineScrittura(LettScritt*);

void Scrivi(LettScritt*, int);
int Leggi(LettScritt*);


#endif
