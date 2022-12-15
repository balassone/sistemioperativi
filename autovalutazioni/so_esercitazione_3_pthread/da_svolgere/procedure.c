#include "header.h"



void inizializza(struct monitor* m){

	m->molo=0;
	m->id_nave=0;

    /* TODO: Inizializzare le variabili dell'algoritmo, il mutex, e le variabili condition */
	pthread_mutex_init(&(m->mutex),NULL);
	pthread_cond_init(&(m->cv_lett),NULL);
	pthread_cond_init(&(m->cv_scritt),NULL);
	m->numlettori=0;
	m->numscrittori=0;
	m->lettori_wait=0;
	m->scrittori_wait=0;
}

void rimuovi (struct monitor* m){
    /* TODO: Disattivare mutex e variabili condition */
	pthread_mutex_destroy(&(m->mutex));
	pthread_cond_destroy(&(m->cv_lett));
	pthread_cond_destroy(&(m->cv_scritt));
}


//SCRITTURA. AGGIORNAMENTO DELLA POSIZIONE DEL TRENO
void scrivi_molo(struct monitor* m, int molo){

    /* TODO: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
     * nella parte della SCRITTURA
     */
	pthread_mutex_lock(&(m->mutex));
	while(m->numlettori>0 || m->numscrittori>0){
		m->scrittori_wait++;
		pthread_cond_wait(&(m->cv_scritt),&(m->mutex));
		m->scrittori_wait--;
	}
	m->numscrittori++;
	pthread_mutex_unlock(&(m->mutex));
	m->molo=m->molo+1; 
	pthread_mutex_lock(&(m->mutex));
	m->numscrittori--;
	if(m->scrittori_wait>0) pthread_cond_signal(&(m->cv_scritt));
	else pthread_cond_broadcast(&(m->cv_lett));
	 pthread_mutex_unlock(&(m->mutex));
}


//LETTURA. RESTITUISCE LA POSIZIONE DEL TRENO
int leggi_molo(struct monitor* m){

    /* TODO: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
     * nella parte della LETTURA
     */
	pthread_mutex_lock(&(m->mutex));
	while(m->numscrittori>0){
		m->lettori_wait++;
		pthread_cond_wait(&(m->cv_lett),&(m->mutex));
		m->lettori_wait--;
	}
	m->numlettori++;
	pthread_mutex_unlock(&(m->mutex));
	int val = m->molo;
	pthread_mutex_lock(&(m->mutex));
	m->numlettori--;
	if(m->numlettori==0) pthread_cond_signal(&(m->cv_scritt));
	pthread_mutex_unlock(&(m->mutex));
	return val;
}

