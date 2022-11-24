#include <pthread.h>

#define TYPE 1
#define NUM_THREADS 10
typedef struct{
	long type;
	int msg;
} Messaggio;

typedef struct{

	int valore;
	pthread_mutex_t mutex;

} Buffer_Thread;
