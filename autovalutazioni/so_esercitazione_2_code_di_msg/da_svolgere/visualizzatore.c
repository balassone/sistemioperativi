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

void visualizzatore(int queue_checksum_visual){

        int i, ret;
        message mess;

        for (i=0; i<NUM_MESSAGES; i++){
				sleep(1);
                printf("[visualizzatore] Ricevo dal processo Checksum...\n");

                ret = msgrcv(queue_checksum_visual,&mess,sizeof(message)-sizeof(long),MSG_TYPE,IPC_NOWAIT);/* TODO: ricevere il messaggio dal processo checksum */

                if(ret<0) {
                        if (errno == ENOMSG){
                                printf("[visualizzatore] Non ci sono più messaggi da ricevere dal processo checksum...exit!\n");
                                break;
                        }
                        else{
                                perror("ERROR!!!");
                                exit(-1);
                        }
                }

                else {
                        printf("[visualizzatore] Messaggio RICEVUTO...PRINT!\n");
                        printf("[visualizzatore] ...............mess.stringa: %s\n", mess.stringa);
                        printf("[visualizzatore] ...............mess.array[0]: %d\n", mess.arr[0]);
                        printf("[visualizzatore] ...............mess.array[1]: %d\n", mess.arr[1]);
                        printf("[visualizzatore] ...............mess.var: %d\n", mess.intero);
                }
        }
        
        exit(0);
}

