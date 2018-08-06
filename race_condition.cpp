#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int count;

void *producer(void *arg)
{
    for(int i = 0; i < 1000; i++ )
	for(int j = 0; j < 1000; j++ )
	    count++;
    pthread_exit(0);

}
void *consumer(void *arg)
{
    for(int i = 0; i < 1000; i++ )
        for(int j = 0; j < 1000; j++ )
            count--;
    pthread_exit(0);

}


int main()
{
    pthread_t tidp, tidc;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&tidp, &attr, producer, NULL);
    pthread_create(&tidc, &attr, consumer, NULL);

    pthread_join(tidp, NULL);
    pthread_join(tidc, NULL);

    printf("count = %d\n", count);

    return 0; 
}
