#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

using std::cout;
void* PrintHello(void* threadid){
	long myid= (long) threadid;
	cout << myid << ": Hello, World!\n";
	pthread_exit(NULL);
}

int main(){

	pthread_t threads[NUM_THREADS];

	int rc;
	long i;	
	for(i=0; i<NUM_THREADS; ++i){
		cout << "Creo il thread " << i << "\n";
		rc=pthread_create(&threads[i],NULL,PrintHello,(void*) i);
		if(rc){
			cout << "Errore thread!\n";
		}
	}

	pthread_exit(NULL);
}
