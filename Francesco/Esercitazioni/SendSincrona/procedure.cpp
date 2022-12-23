#include "header.h"
#include <unistd.h>
#include <string.h>
int queue1;
int queue2;

void initqueues(){
	queue1=msgget(IPC_PRIVATE,IPC_CREAT|0664);
	queue2=msgget(IPC_PRIVATE,IPC_CREAT|0664);
}

void removequeues(){
	msgctl(queue1,IPC_RMID,NULL);
	msgctl(queue2,IPC_RMID,NULL);
}

void send(Messaggio* m, int queue){
	Messaggio m1, m2;
	m1.type=RTS;
	strcpy(m1.msg,"RTS");
	msgsnd(queue1,(void*)&m1,sizeof(Messaggio)-sizeof(long),0);
	msgrcv(queue2,(void*)&m2,sizeof(Messaggio)-sizeof(long),OTS,0);
	msgsnd(queue,(void*)m,sizeof(Messaggio)-sizeof(long),0);
}

void receive(Messaggio* m, int queue){
	Messaggio m1, m2;
	msgrcv(queue1,(void*)&m1,sizeof(Messaggio)-sizeof(long),RTS,0);
	m2.type=OTS;
	strcpy(m2.msg,"OTS");
	msgsnd(queue2,(void*)&m2,sizeof(Messaggio)-sizeof(long),0);
	msgrcv(queue,(void*)m,sizeof(Messaggio)-sizeof(long),MESSAGGIO,0);
}
