#include<iostream>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<stdexcept>
using std::cout;
using std::endl;
int main(){
	key_t shm_key=IPC_PRIVATE;
	int ds_shm=shmget(shm_key,sizeof(int),IPC_CREAT|0664);
	if(ds_shm<0) throw std::runtime_error("Errore shmget");
	int* ciao=(int*) shmat(ds_shm,NULL,0);
	int pid=fork();
	if(pid<0) throw std::runtime_error("Errore Fork");
	if(pid==0){
		cout << "Sono il figlio!" << endl;
		*ciao=27;
		exit(0);
	}
	if(pid>0){
		wait(NULL);
		cout << "Sono il padre!" << endl;
		cout << *ciao;
	}
	shmctl(ds_shm,IPC_RMID,NULL);
	return 0;
}
