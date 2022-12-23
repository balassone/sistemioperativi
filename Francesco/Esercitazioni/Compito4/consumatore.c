#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"


int main() {
	int pid;
	//TODO: completare l'inizializzazione code
    key_t msg_req_key = ftok(".",'q');/*..*/
	key_t msg_res_key = ftok(".",'s');/*..*/

	int queue_req = msgget(msg_req_key,IPC_CREAT|0664);/*..*/
	int queue_res = msgget(msg_res_key,IPC_CREAT|0664);/*..*/

	int i;
	for (i=0; i < NUM_CONS; i++) {
		req msg;
		//TODO preparazione messaggio
		msg.type=1;
		printf("CONSUMATORE %d: invio richiesta \n",getpid());
		//TODO invio richiesta
		msgsnd(queue_req,(void*)&msg, sizeof(req)-sizeof(long),0);
		res risp;
		//TODO ricezione risposta
		msgrcv(queue_res,(void*)&risp,sizeof(res)-sizeof(long),0,0);
		printf("CONSUMATORE %d: letto valore: %d\n",getpid(),risp.value);
		sleep(1);
	}
	//TODO rimozione code
	msgctl(queue_req,IPC_RMID,NULL);
	msgctl(queue_res,IPC_RMID,NULL);
	return 0;
}
