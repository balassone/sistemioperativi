#include <pthread.h>
#ifndef HEADER_H
#define HEADER_H
typedef long msg;

typedef struct{
	pthread_mutex_t mutex;

	pthread_cond_t ok_prod_cv;
	pthread_cond_t ok_cons_cv;

	int ok_produzione;
	int ok_consumo;

	msg mess;

} ProdCons;

void* Consumatore(void*);
void* Produttore(void*);

void Produci(ProdCons*, msg);
msg Consuma(ProdCons*);

void InizioConsumo(ProdCons*);
void FineConsumo(ProdCons*);
void InizioProduzione(ProdCons*);
void FineProduzione(ProdCons*);

#endif //HEADER_H
