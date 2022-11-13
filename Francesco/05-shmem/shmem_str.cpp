#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>

using std::cout;
using std::endl;

int main(){
	key_t shm_key=ftok(".",'a');
	int ds_shm=shmget(shm_key,256, IPC_CREAT|0664);
	if(ds_shm<0) cout << "Errore!\n";
	char* a=(char*)shmat(ds_shm,NULL,0);
	int pid=fork();
	if(pid==0){
		cout << "Copio la stringa...\n";
		strcpy(a,"CiaoSbri");
		exit(1);
	}
	if(pid>0){
		wait(NULL);
		cout << "La stringa e': " << a << endl;
	}
	shmctl(ds_shm,IPC_RMID,NULL);

	return 0;
}
