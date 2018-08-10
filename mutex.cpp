#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

int r1 = 0,r2=0,r3=0;

void *do_one_thing(void *pnum_times) {
    int x;
    
    if(r3>0){
        x=r3;
        r3--;
    }
	else
        x=5;

    for (int i =0;i<4;i++){
        printf("doing one thing,%d\n",x);
        for(int j=0;j<10000;j++)
            x++;
        (*(int *)pnum_times)++;
    }
    pthread_exit(0);
}

void *do_another_thing(void *pnum_times){
	pthread_exit(0);

}
int main(int argc,char *argv[]){
	
	pthread_t thread1 ,thread2;

	if(argc >1)
		r3= atoi(argv[1]);

	pthread_create(&thread1,NULL,do_one_thing,(void *)&r1);
	pthread_create(&thread2,NULL,do_another_thing,(void *)&r2);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	
	return 0;
}
