#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// This program creates a number N of threads specified on the argv

void	*routine(void *i)
{
	printf("Hello from thread-%d (%lu)\n", *(int*)i, pthread_self());
	return(NULL);
}

int	main(int argc, char *argv[])
{
	int	nb;
	int	i;
	pthread_t	*threads;

	nb = atoi(argv[1]);
	threads = malloc(sizeof(pthread_t) * nb);
	i = 0;
	while (i < nb)
	{
		pthread_create(&threads[i], NULL, routine, (void*)&i);
		printf("Creating thread-%d (%lu)\n", i, threads[i]);
		sleep(1);
		i++;
	}
	return(0);
}
