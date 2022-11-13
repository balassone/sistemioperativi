#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char*argv[]){
	while(1){
		int pid=fork();
		switch(pid){
			case -1:
				printf("Errorone\n");
				break;
			case 0:
				printf("Sono il figlio!, il mio PID e' %d\n",getpid());
				execl(argv[1],argv[1],argv[2],argv[3],NULL);
				printf("Se arrivo qui stai sbagliando!\n");
				kill(getppid(), SIGKILL);
				exit(1);
				break;
			default:
				printf("Sono il papa', con PID %d\n",getpid());
				wait(NULL);
				printf("Successo\n");
				printf("Il papa' termina");
				exit(0);
				break;
		}
	}
	return 0;
}
