#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	struct	timeval	tv1;
	struct	timeval	tv2;
	int	delta_time;

	gettimeofday(&tv1, NULL);
	usleep(250000);
	gettimeofday(&tv2, NULL);
	delta_time = (tv2.tv_usec - tv1.tv_usec) / 1000;
	printf("delta time = %d milliseconds\n", delta_time);
	return (0);
}
