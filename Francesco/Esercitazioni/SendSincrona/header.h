#ifndef HEADER_H
#define HEADER_H
#include <sys/msg.h>
#define RTS 0
#define OTS 1
#define MESSAGGIO 2

typedef struct{
	long type;
	char* msg;
} Messaggio;

void send(Messaggio* m, int queue);
void receive(Messaggio* m,int queue);
void initqueues();
void removequeues();
#endif
