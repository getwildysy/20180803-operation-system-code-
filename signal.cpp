#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void handler(int signo){
	
	switch (signo){
	case SIGINT:
		printf("catch a signal -SIGINT\n");
		break;
	case SIGALRM:
		printf("catch a signal -SIGNALALRM\n");
		break;
	case SIGVTALRM:
		printf("catch a signal -SIGVTALRM\n");
		break;
	
	}
}


int main(){
	
	struct itimerval value ,ovalue;

	signal(SIGHUP,handler);
	signal(SIGINT,handler);
	signal(SIGQUIT,handler);

	pause();
	

	signal(SIGALRM,handler);
	signal(SIGVTALRM,handler);

	value.it_value.tv_sec =1;
	value.it_value.tv_usec =0;
	value.it_interval.tv_sec=1;
	value.it_interval.tv_usec=0;
	setitimer(ITIMER_REAL,&value,&ovalue);
	
	while (1);
	
	return 0 ;
}
