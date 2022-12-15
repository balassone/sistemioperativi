#define MSG_TYPE 1
#define STRING_MAX_DIM 11
#define INT_MAX_DIM 2


#define NUM_FILTER 1
#define NUM_CHECKSUM 1
#define NUM_VISUAL 1

#define NUM_GENERATORS 4
#define DIM_QUEUE 4
#define VARCOND_GEN_PRODUTTORI 0
#define VARCOND_GEN_CONSUMATORI 1

#define NUM_MESSAGES 8
#define DIM 4

#include "monitor_signal_continue.h"

typedef struct {
        
    /* TODO: Definire il messaggio */
	long type;
	char stringa[STRING_MAX_DIM];
	int arr[INT_MAX_DIM];
	int intero; //Inizialmente 0
} message;

#define CV_PROD 0
#define CV_CONS 1

struct ProdConsGen {
    
    /* TODO: Definire le variabili per la sincronizzazione dei processi generatori prod/cons */
    message queue[DIM];
	int testa;
	int coda;
	Monitor m;
};

void generatore_produttore(struct ProdConsGen *);
void generatore_consumatore(struct ProdConsGen *,  int);

void filtro(int, int);
void checksum(int , int);
void visualizzatore(int);
