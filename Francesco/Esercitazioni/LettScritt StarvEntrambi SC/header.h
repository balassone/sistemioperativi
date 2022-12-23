#ifndef HEADER_H
#define HEADER_H

#include "monitor.h"

#define CV_LETT 0
#define CV_SCRITT 1

typedef struct{
	int buffer; //Inizializzo 0
	int numlettori; //Inizializzo 0
	int numscrittori; //Inizializzo 0

	Monitor m; //Init e Remove
} LettScritt;

void inizioLettura(LettScritt*);
void fineLettura(LettScritt*);
void inizioScrittura(LettScritt*);
void fineScrittura(LettScritt*);

#endif //HEADER_H
