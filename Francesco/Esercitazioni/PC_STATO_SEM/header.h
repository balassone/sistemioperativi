#ifndef HEADER_H
#define HEADER_H

#define MUTEXP 0 //1
#define MUTEXC 1 //1
#define SPAZIO_DISP 2 //DIM
#define NUM_MESS 3 // 0
#define DIM 10

#define LIBERO 0
#define IN_USO 1
#define OCCUPATO 2

typedef struct{
	int buffer[DIM]; //0
	int stato[DIM]; //LIBERO
} ProdCons;

void Produttore(ProdCons* pc, int semid, int val){
	Wait_Sem(semid,SPAZIO_DISP);
	Wait_Sem(semid,MUTEXP);
	int i=0;
	while(i<dim && pc->stato[i]!=LIBERO) i++;
	pc->stato[i]=IN_USO;
	Signal_Sem(semid,MUTEXP);
	pc->buffer[i]=val;
	pc->stato[i]=OCCUPATO;
	Signal_Sem(semid,NUM_MESS);
}

int Consumatore(ProdCons* pc, int semid){
	Wait_Sem(semid,NUM_MESS);
	Wait_Sem(semid,MUTEXC);
	int i=0;
	while(i<DIM && pc->stato[i]!=OCCUPATO) i++;
	pc->stato[i]=IN_USO;
	Signal_Sem(semid,MUTEXC);
	int val=pc->buffer[i];
	pc->stato[i]=LIBERO;
	Signal_Sem(semid,SPAZIO_DISP);
	return val;
}

#endif
