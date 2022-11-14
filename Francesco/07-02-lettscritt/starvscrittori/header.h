#ifndef HEADER_H
#define HEADER_H
#define MUTEXL 0
#define SYNCH 1
#define NUMVOLTE 6
#include "semafori.h"
typedef long msg;
typedef struct {
	int numlettori;
	msg messaggio;
} Buffer;
void Lettore(int, Buffer*);
void Scrittore(int, Buffer*);
#endif
