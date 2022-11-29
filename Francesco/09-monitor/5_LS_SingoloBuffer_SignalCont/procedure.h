#ifndef PROCEDURE_H
#define PROCEDURE_H

#include "monitor_signal_continue.h"

typedef struct{
	int buf;

	int numlettori;
	int numscrittori;
	
	Monitor m;

} LettScritt;

#define CV_LETT 0
#define CV_SCRITT 1

void Scrittura(LettScritt*, int);
int Lettura(LettScritt*);

#endif //PROCEDURE_H
