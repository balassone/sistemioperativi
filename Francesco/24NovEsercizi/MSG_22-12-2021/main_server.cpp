#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include "header.h"
#include <stddef.h>
int main(){
	key_t msg_key={ftok(".",'a')};
	int qid=msgget(msg_key,IPC_CREAT|0664);

	pthread_attr_t attr;
	pthread_t threads[NUM_THREADS];
	Buffer_Thread* tb= new Buffer_Thread;
	pthread_mutex_init(tb->mutex);
	tb->valore=0;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
}
