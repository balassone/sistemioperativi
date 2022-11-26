#ifndef HEADER_H
#define HEADER_H

#include "monitor_hoare.h"

#define N_GENERATORI 3
#define N_CALCOLATORI 3
#define N_PRINTERS 3

// DONE DEFINIRE MACRO DI SUPPORTO

#define CV_SCRITTORI 0
#define CV_LETTORI 1

#define SOMMA 1
#define PRODOTTO 2
#define DIVISIONE 3

#define N_GENERAZIONI 4
#define N_CALCOLI 2 // Assumiamo che un calcolo corrisponda a 2 chiamate di msgrcv() e 1 chiamata di inserisci_risultato, in totale ogni processo effettua 4 chiamate di msgget() e 2 di inserisci_risultato
#define N_STAMPE 6

struct MonitorRisultati {
	//DONE riempire struttura
	float risultati[3]; 

	int numlettori;
	int numscrittori;

	Monitor m;
};


void inserisci_risultato(struct MonitorRisultati * ls, float valore, int operazione);
float* leggi_risultati(struct MonitorRisultati * ls);

typedef struct {
	// DONE DEFINIRE TIPO MESSAGGIO
	long type;
	float num;
} Messaggio;

void calcolo(struct MonitorRisultati * ls, int operazione, int mailbox);
void generazione(int operazione, int mailbox);
void printer(struct MonitorRisultati * ls);

#endif
