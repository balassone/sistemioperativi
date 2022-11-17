#ifndef HEADER_H
#define HEADER_H

#define MESSAGGIO 1

typedef char msg[40];

typedef struct{
	long tipo;
	msg mess;
} Messaggio;

void produttore(int coda, char* m);
void consumatore(int coda);
void printMsgInfo(int queue);
#endif
