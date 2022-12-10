#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
	int			i;
	struct timeval tv1;
	int			t_eat;
	int			t_sleep;
	long int	start_time;
	int			t_die;
	int			times_eaten;
	long int	last_meal;
} t_data;

pthread_mutex_t	mutex;

long int	current_time()
{
	struct	timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	eat(t_data **data)
{
	//pthread_mutex_lock(&mutex);
	int	time_diff;

	(*data)->times_eaten++;
	time_diff = (current_time() - (*data)->start_time) / 1000;
	(*data)->last_meal = current_time();
	printf("%d last meal t: %ld\n", (*data)->i, (*data)->last_meal);
	printf("%d philo %d is eating\n", time_diff, (*data)->i);
	usleep((*data)->t_eat * 1000);
	//pthread_mutex_unlock(&mutex);
}

void	philo_sleep(t_data data)
{
	int	time_diff;

	time_diff = (current_time() - data.start_time) / 1000;
	printf("%d philo %d is sleeping\n", time_diff, data.i);
	usleep(data.t_sleep * 1000);
}

void	think(t_data data)
{
	int	time_diff;

	time_diff = (current_time() - data.start_time) / 1000;
	printf("%d philo %d is thinking\n", time_diff, data.i);
}

void	*routine(void *arg)
{
	struct	timeval	tv2;
	int	time_diff = 0;
	t_data	*data;

	data = (t_data*)arg;
	//while (1)
	//{
		eat(&data);
		//printf("times eaten: %d\n", data.times_eaten);
	//	if (data.times_eaten == 3)
	//		break;
		//philo_sleep(*data);
		//think(*data);
	//}
	return(NULL);
}

void	*check_philo(void *arg)
{
	int		time_diff;
	long int	tst;
	t_data	data;
	data = *(t_data*)arg;
	int i = 0;
	while (i < 2)
	{
		time_diff = current_time() - data.last_meal;
		printf("last meal: %ld\n", data.last_meal);
		usleep(200000);
		i++;
	}

}

int	main()
{
	pthread_t	*philo;
	pthread_t	monitoring;
	t_data		data;

	data.t_eat = 100;
	data.t_sleep = 100;
	data.t_die = 200;
	data.times_eaten = 0;
	data.last_meal = 0;
	philo = malloc(sizeof(pthread_t) * 2);
	data.i = 1;
	pthread_mutex_init(&mutex, NULL);
	gettimeofday(&data.tv1, NULL);
	data.start_time = data.tv1.tv_sec * 1000000 + data.tv1.tv_usec;
	while (data.i <= 2)
	{
		pthread_create(&philo[data.i], NULL, &routine, &data);
		usleep(2000);
		data.i++;
	}
	pthread_create(&monitoring, NULL, &check_philo, &data);
	//usleep(200000);
	data.i = 1;
	while (data.i <= 2)
	{
		pthread_join(philo[data.i], NULL);
		data.i++;
	}
	pthread_join(monitoring, NULL);
	pthread_mutex_destroy(&mutex);
	return(0);
}
