#include <unistd.h>
#include "header.h"
int main(){
	int pid;
	key_t msg_req_key=ftok(".",'a');
	key_t msg_res_key=ftok(".",'a');

	int queue_req=msgctl(msg_req_key,IPC_CREAT|0664);
	int queue_res=msgctl(msg_res_key,IPC_CREAT|0664);

	int i;
	for(i=0; i<NUM_CONS; i++){
		req msg;
		msg.type=1;

		msgsnd(queue_req,&msg,sizeof(msg)-sizeof(long),0);
		res risp;
		msgrcv(queue_res,&msg,sizeof(msg)-sizeof(long),0,0); //TIPO MESSAGGIO 0 -> PRELEVA TUTTO IN MODO FIFO
	}
}
