#include <sys/types.h>
#include <sys/msg.h>
#include <wait.h>
#include <stdio.h>
#include <unistd.h>
#include "header.h"

int main(){
	key_t msg_key=ftok(".",'a');
	int qid=msgget(msg_key,IPC_CREAT|0664);
	for(int i{0}; i<5; ++i){
		Messaggio mess;
		mess.type=TYPE;
		mess.msg=i;

		int ret=msgsnd(qid,&mess,sizeof(Messaggio)-sizeof(long),0);
	}
}
