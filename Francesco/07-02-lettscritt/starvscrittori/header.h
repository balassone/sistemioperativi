#ifndef HEADER_H
#define HEADER_H
#define MUTEXL 0
#define SYNCH 1
typedef long msg;
typedef struct{
	int numlettori;
	msg messaggio;
} Buffer;

void lettore(int, Buffer*);
void scrittore(int, Buffer*);
#endif
