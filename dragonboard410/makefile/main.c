#include <stdio.h>
#include <pthread.h>

static void * Task(void * param);

int main ()
{
	int status;
	pthread_t thread;

    status = pthread_create(&thread, NULL, Task, NULL);

    if(status)
    {
    	return -1;
    }

    pthread_join(thread, NULL);

	return (0) ;
}

static void * Task(void * param)
{
	int i = 10;

	while(i--){
		printf ("Dragonboard410c: Hello World!\n");
	}

	return NULL;
}