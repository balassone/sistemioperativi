#include "semafori.h"
#include "procedure.h"
#include <iostream>
void produttore(int* buf, int sem){
	std::cout << "Produttore aspetta...\n";
	Wait_Sem(sem, SPAZIO_DISPONIBILE);
	std::cout << "Produttore scrive...\n";
	*buf=8;
	std::cout << "Produttore segnala...\n";
	Signal_Sem(sem, MESSAGGIO_DISPONIBILE);
}

void consumatore(int* buf, int sem){
	std::cout << "Consumatore aspetta...\n";
	Wait_Sem(sem, MESSAGGIO_DISPONIBILE);
	
	std::cout << "Valore consumato: " << *buf;
	Signal_Sem(sem, SPAZIO_DISPONIBILE);
}
