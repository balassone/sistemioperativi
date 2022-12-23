#ifndef HEADER_H
#define HEADER_H

#include "semafori.h"

#define MUTEXL 0
#define MUTEXS 1
#define MUTEX 2
#define SYNCH 3

typedef struct {
	int buffer;
	int numlettori;
	int numscrittori;
} LettScritt;

void inizioLettura(LettScritt*, int);
void fineLettura(LettScritt*, int);
void inizioScrittura(LettScritt*, int);
void fineScrittura(LettScritt*, int);
void Scrittore(LettScritt*, int, int);
int Lettore(LettScritt*, int);

#endif
