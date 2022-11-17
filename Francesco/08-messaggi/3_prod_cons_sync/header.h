#ifndef HEADER_H
#define HEADER_H

#define RTS 1
#define OTS 2
#define MESSAGGIO 3

typedef char msg[40];
typedef struct {
	long tipo;
	msg mess;
} Messaggio;

void initQueues();
void rmQueues();
void sendSync(Messaggio* m, int queue);
void receiveBloc(Messaggio* m, int queue, int tipomess);

void Producer(int queue, char*);
void Consumer(int queue);

#endif
