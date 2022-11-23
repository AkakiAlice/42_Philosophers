#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// This program creates a thread

void	*routine(void *main_id)
{
	pthread_t	id = (pthread_t)main_id;
	printf("new thread %lu\n", pthread_self());
	printf("main thread from new t %lu\n", id);
	return(NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	thread;
	long		tid;

	tid = pthread_self();
	printf("main thread id: %ld\n", tid);
	pthread_create(&thread, NULL, routine, (void *)tid);
	printf("new thread id from main: %lu\n", thread);
	pthread_join(thread, NULL);
	return(0);
}
