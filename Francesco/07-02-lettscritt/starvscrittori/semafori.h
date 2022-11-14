#ifndef SEMAFORI_H
#define SEMAFORI_H
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int Wait_Sem(int sem_id, int numsem);
int Signal_Sem(int sem_id, int numsem);

#endif
