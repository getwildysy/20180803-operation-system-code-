#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

/*
* ./a.out main a3 0 2 4 5 7
*/

#define NTHR 8

int alarmthread = -1;
bool block[NTHR]={0};
sigset_t mask;
pthread_t tid[NTHR];

void handler(int signo){
}


void set_timer(){
}

void *thr_fn(void *arg){
	int id = (intptr_t)arg;
	printf("thread %d\n starts......",id);

	if(block[id]){

		printf("thread %d blocking SIGALRM.\n",id);
		pthread_sigmask(SIG_BLOCK,&mask,NULL);
	}	

	if(alarmthread == id){
		printf("thread %d:setting alarm.\n",id);
		set_timer();	
		while(1)
			pause();
	}
	pthread_exit(0);
}

int main(int argc,char *argv[]){

	bool doblock = false;
	int id,i;
	struct sigaction   act;

	for (i=0; i< argc ; i++){
		if(strcmp(argv[i],"main")==0)
			doblock = true;
		else if (argv[i][0]=='a')
			alarmthread = argv[i][1];
		else {
			id =atoi(argv[i]);
			block[id]= true;
		}
	}

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM,&act,NULL);

	sigemptyset(&mask);
	sigaddset(&mask,SIGALRM);
	
	for (i=0;i<NTHR;i++){
		pthread_create(&tid[i],NULL,thr_fn,(void *)(intptr_t)i);
	}


/*
	value.it_value.tv_sec =1;
	value.it_value.tv_usec =0;
	value.it_interval.tv_sec=1;
	value.it_interval.tv_usec=0;
	setitimer(ITIMER_REAL,&value,&ovalue);
	
	while (1);
*/	
	return 0 ;
}
