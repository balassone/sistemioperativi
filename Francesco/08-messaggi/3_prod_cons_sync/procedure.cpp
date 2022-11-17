#include "header.h"
#include <sys/msg.h>
#include <string.h>

static int queue1;
static int queue2;

void initQueues(){
	queue1=msgget(IPC_PRIVATE,IPC_CREAT|0664);
	queue2=msgget(IPC_PRIVATE,IPC_CREAT|0664);
}

void rmQueues(){
	msgctl(queue1,IPC_RMID,0);
	msgctl(queue2,IPC_RMID,0);
}

void sendSync(Messaggio* m, int queue){
	Messaggio m1,m2;
	m1.tipo=RTS;
	strcpy(m1.mess,"ReadyToSend");
	msgsnd(queue1,(void*)&m1, sizeof(Messaggio)-sizeof(long),0);
	msgrcv(queue2,(void*)&m2, sizeof(Messaggio)-sizeof(long),OTS,0);
	msgsnd(queue,(void*)m,sizeof(Messaggio)-sizeof(long),0);
}

void receiveBloc(Messaggio* m, int queue, int tipomess){
	Messaggio m1, m2;
	msgrcv(queue1,(void*)&m1, sizeof(Messaggio)-sizeof(long),RTS,0);
	m2.tipo=OTS;
	strcpy(m2.mess,"OkToSend");
	msgsnd(queue2,(void*)&m2,sizeof(Messaggio)-sizeof(long),0);
	msgrcv(queue,(void*)m,sizeof(Messaggio)-sizeof(long),tipomess,0);
}

void Producer(int queue, char* m){
	Messaggio me;
	me.tipo=MESSAGGIO;
	strcpy(me.mess,m);
	sendSync(&me,queue);
}

void Consumer(int queue){
	Messaggio m;
	receiveBloc(&m,queue,MESSAGGIO);
	//print
}
