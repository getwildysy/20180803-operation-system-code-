#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_key_t house_key;

void bar(){
	float *f=(float *)pthread_getspecific(house_key);
	printf("thread %d : house_key=%f\n",pthread_self(),*f);
}

void *foo(void *arg)
{
 	pthread_setspecific(house_key,arg);
	bar();
	pthread_exit(0);
}


int main()
{
	pthread_t tid1, tid2;
	pthread_attr_t attr;
	float f1=1.414,f2=3.1415;

	pthread_key_create(&house_key,NULL);
	
	pthread_attr_init(&attr);
	pthread_create(&tid1, &attr, foo, &f1);
	pthread_create(&tid2, &attr, foo, &f2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

    return 0; 

}
