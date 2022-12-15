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

void checksum(int queue_filter_checksum, int queue_checksum_visual){

        int ret, i, j, checksum=0;
        message mess;

        for (j=0; j<NUM_MESSAGES; j++){

                printf("[checksum] Ricevo dal processo Filter...\n");

                ret = msgrcv(queue_filter_checksum,&mess,sizeof(message)-sizeof(long),MSG_TYPE,IPC_NOWAIT);/* TODO: ricevere il messaggio dal processo filter */
            
                if(ret<0) {
                        if (errno == ENOMSG){
                                printf("Non ci sono più messaggi da ricevere dal processo filter...exit!\n");
                                break;
                        }
                        else{
                                perror("ERROR!!!");
                                exit(-1);
                        }
                }
                /* TODO: Calcolare la checksum e inviarla al visualizzatore  */
               	for(i=0; i<STRING_MAX_DIM; ++i){
					checksum+=mess.stringa[i];
				} 
				for(i=0; i<INT_MAX_DIM; ++i){
					checksum+=mess.arr[i];
				}
				sleep(1);
				mess.intero=checksum;
                printf("[checksum] Invio messaggio di CHECKSUM al Visualizzatore...\n");
        		msgsnd(queue_checksum_visual,&mess,sizeof(message)-sizeof(long),0);
		}
        
        exit(0);
}

