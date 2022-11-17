#ifndef PROCEDURE_H
#define PROCEDURE_H
#define MUTEXL 0
#define MUTEXS 1
#define MUTEX 2
#define SYNCH 3

typedef long msg;

typedef struct {
	int numlettori;
	int numscrittori;
	msg messaggio;
} Buffer;

void lettore(int, Buffer*);
void scrittore(int, Buffer*);

#endif
