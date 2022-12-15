#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "header.h"


void generatore_produttore(struct ProdConsGen *pc){
        
    /* TODO: utilizzare il costrutto monitor per la produzione del messaggio */
	enter_monitor(&(pc->m));
	while((pc->testa+1)%DIM==pc->coda){
		wait_condition(&(pc->m),CV_PROD);
	}
	message msg;
	srand(getpid()*time(NULL));
	for(int i=0; i<(STRING_MAX_DIM)-1; ++i){
		msg.stringa[i]='a'+(rand()%26);
	}
	msg.stringa[10]='\0';
	msg.arr[0]=rand()%10;
	msg.arr[1]=rand()%10;
	msg.type=MSG_TYPE;
	msg.intero=0;
	sleep(1);
    printf("[generatore_produttore] Messaggio generato!\n");
    printf("[generatore_produttore] ...............msg.stringa: %s\n", msg.stringa);
    printf("[generatore_produttore] ...............msg.array[0]: %d\n", msg.arr[0]);
    printf("[generatore_produttore] ...............msg.array[1]: %d\n", msg.arr[1]);
    printf("[generatore_produttore] ...............msg.var: %d\n", msg.intero);
 
    /* TODO: ... */
	pc->queue[pc->testa]=msg;
	pc->testa=(pc->testa+1)%DIM;
	signal_condition(&(pc->m),CV_CONS);
	leave_monitor(&(pc->m));
}

void generatore_consumatore(struct ProdConsGen *pc, int ds_queue_gen_filter){

    /* TODO: utilizzare il costrutto monitor per la consumazione del messaggio e l'invio verso il processo filter */
   	enter_monitor(&(pc->m));
	while(pc->testa==pc->coda) wait_condition(&(pc->m),CV_CONS);
	sleep(1);
    printf("[generatore_consumatore] Messaggio CONSUMATO!\n");
    printf("[generatore_consumatore] ...............msg.stringa: %s\n", pc->queue[pc->coda].stringa);
    printf("[generatore_consumatore] ...............msg.array[0]: %d\n", pc->queue[pc->coda].arr[0]);
    printf("[generatore_consumatore] ...............msg.array[1]: %d\n", pc->queue[pc->coda].arr[1]);
    printf("[generatore_consumatore] ...............msg.var: %d\n", pc->queue[pc->coda].intero);
    
    int ret = msgsnd(ds_queue_gen_filter,&pc->queue[pc->coda],sizeof(message)-sizeof(long),0);/* TODO: invio del messaggio consumato al processo filter */
    
    if (ret<0){
            perror("msgsnd del messaggio on ds_queue_gen_filter FALLITA!");
            exit(-1);
    }
    printf("[generatore_consumatore] Messaggio INVIATO!\n");
    
    /* TODO: ... */
	pc->coda=(pc->coda+1)%DIM;
	signal_condition(&(pc->m),CV_PROD);
	leave_monitor(&(pc->m));
}

