#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

int main(){
	key_t msg_key=ftok(".",'a');
	int qid = msgget(msg_key,IPC_CREAT|0664);
	if(qid<0) return -1;
	
	pid_t pid_c, pid_s;

	pid_c=fork();
	if(pid_c==0){
		execve("./main_client",NULL,NULL);
	}

	pid_s=fork();

	if(pid_s==0){
		execve("./main_server",NULL,NULL);
	}

	for(int i{0}; i<2; ++i){
		wait(NULL);
	}

	msgctl(qid,IPC_RMID,0);

	return 0;
}
