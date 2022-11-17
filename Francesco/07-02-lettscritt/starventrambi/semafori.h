#ifndef SEMAFORI_H
#define SEMAFORI_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/wait.h>
#include <sys/sem.h>

int Wait_Sem(int, int);
int Signal_Sem(int, int);

#endif
