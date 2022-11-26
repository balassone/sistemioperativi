#include "procedure.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <time.h>


float* leggi_risultati(struct MonitorRisultati * ls) {

	float* risultati = malloc(sizeof(float)*3);//DONE completare 
	
	printf("[%ld] Lettura - ingresso monitor\n", getpid());

	// DONE lettura

	enter_monitor(&(ls->m));
	if(ls->numscrittori>0){
		wait_condition(&(ls->m),CV_LETTORI);
	}

	ls->numlettori=ls->numlettori+1;

	signal_condition(&(ls->m),CV_LETTORI);
	leave_monitor(&(ls->m));

	for(int i=0; i<3; ++i){
		risultati[i]=ls->risultati[i];
	}

	printf("[%ld] Lettura - uscita monitor\n", getpid());

	enter_monitor(&(ls->m));
	ls->numlettori=ls->numlettori-1;
	if(ls->numlettori==0) signal_condition(&(ls->m),CV_SCRITTORI);
	leave_monitor(&(ls->m));
	return risultati;

}


void inserisci_risultato(struct MonitorRisultati * ls, float valore, int operazione) {

	// DONE scrittura
	
	printf("[%ld] Scrittura - ingresso monitor\n", getpid());
	enter_monitor(&(ls->m));

	if(ls->numlettori>0 || ls->numscrittori>0){
		wait_condition(&(ls->m),CV_SCRITTORI);
	}
	
	ls->numscrittori=ls->numscrittori+1;

	leave_monitor(&(ls->m));

	printf("[%ld] Scrittura - valore [%f] operazione %d\n", getpid(),valore, operazione);
	ls->risultati[operazione-1]=valore;
	
	
	enter_monitor(&(ls->m));
	
	ls->numscrittori=ls->numscrittori-1;

	if(queue_condition(&(ls->m),CV_SCRITTORI)>0) signal_condition(&(ls->m),CV_SCRITTORI);
	else signal_condition(&(ls->m),CV_LETTORI);
	
	leave_monitor(&(ls->m));
	printf("[%ld] Scrittura - uscita monitor\n",getpid());
}

void calcolo(struct MonitorRisultati * ls, int operazione, int mailbox){
	for(int i=0; i<N_CALCOLI; ++i){
		Messaggio m1, m2;

		float val1, val2, risultato;

		msgrcv(mailbox,(void*)&m1, sizeof(Messaggio)-sizeof(long),operazione,0);
		msgrcv(mailbox,(void*)&m2, sizeof(Messaggio)-sizeof(long),operazione,0);

		val1=m1.num;
		val2=m2.num;

		switch(operazione){
			case SOMMA:
				risultato=val1+val2;
				break;
			case PRODOTTO:
				risultato=val1*val2;
				break;
			case DIVISIONE:
				risultato=val1/val2;
				break;
		}
		sleep(1);
		inserisci_risultato(ls,risultato,operazione);
	
	}
}

void generazione(int operazione, int mailbox) {
	for(int i=0; i<N_GENERAZIONI; ++i){ //Ogni processo genera 4 operandi
		srand(getpid()*i+time(NULL));
		// DONE completa
		float operando = rand() % 20 + 1;
		Messaggio m;

		m.type=operazione;
		m.num=operando;

		msgsnd(mailbox,(void*)&m,sizeof(Messaggio)-sizeof(long),0);
		sleep(1); //Non necessario, aggiunto solo per dare più tempo a rand() per randomizzare. Funziona anche senza!!
	}
}

void printer(struct MonitorRisultati * ls) {
	float* risultati;
	for (int i = 0 ; i < 4; i++) { //4 per dare tutto il tempo di stampare i 6 risultati differenti?
		sleep(2);
		risultati = leggi_risultati(ls);
		printf("[%ld] Risultati 1: %f, 2: %f, 3: %f\n",getpid(), risultati[0], risultati[1], risultati[2]);
		//DONE COMPLETA DEALLOCAZIONE risultati
		free(risultati);
	}
}
