#ifndef _HEADER_
#define _HEADER_

#include <pthread.h>

#define FTOK_PATH_Q "."
#define FTOK_CHAR_Q 'p'

#define MESSAGGIO 1

/* TBD: Definire qui una struttura dati per i messaggi */
typedef struct{
	long type;
	int msg;
} Messaggio;

typedef struct {

    int valore; //Inizializza a 0
    
    /* TBD: Estendere questa struttura, in modo da realizzare la 
     *      mutua esclusione per l'accesso al valore
     */
	 pthread_mutex_t mutex; //Inizializza e Distruggi

} BufferMutuaEsclusione;

#endif
