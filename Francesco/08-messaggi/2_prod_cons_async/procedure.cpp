#include "header.h"
#include <sys/msg.h>
#include <string.h>
#include <time.h>
void produttore(int queue, char* c){
	Messaggio m;
	m.tipo=MESSAGGIO;
	strcpy(m.mess,c);
	msgsnd(queue,(void*)&m,sizeof(Messaggio)-sizeof(long),IPC_NOWAIT);
}

void consumatore(int queue){
	Messaggio m;
	msgrcv(queue,(void*)&m,sizeof(Messaggio)-sizeof(long),MESSAGGIO,0);
}

void printMsgInfo(int queue){
	struct msqid_ds mid;
	msgctl(queue,IPC_STAT,&mid);
	char* time_sender=ctime(&mid.msg_stime);
	char* time_receiver=ctime(&mid.msg_ctime);
	char* time_ctime=ctime(&mid.msg_ctime);
	unsigned long num=mid.msg_qnum;
}
