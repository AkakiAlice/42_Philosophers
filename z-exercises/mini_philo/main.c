#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
	long		start_time;
	int			must_eat;
	pthread_t	monitoring;
	int			nb_philos;
	int			all_satisfied;
	int			died;
	int			t_die;
}			t_data;

typedef struct s_node
{
	struct s_node	*prev;
	struct s_node	*next;
	int				philo_id;
	int				nb_eat;
	int				satisfied;
	long			last_meal;
	pthread_t		philo;
	t_data			*data;
}			t_node;

pthread_mutex_t	mutex;


/*typedef struct s_data
{
	t_node		*head;
	int			t_eat;
	int			t_sleep;
	long int	start_time;
	struct timeval tv1;
}			t_data;*/

//linked list
void	add_first_node(t_node **head, t_node *new)
{
	*head = new;
	new->next = *head;
	new->prev = *head;
}

void	add_node(t_node **head, t_node *new)
{
	t_node	*aux;

	aux = *head;
	while (aux->next != *head)
	{
		aux = aux->next;
	}
	aux->next = new;
	new->prev = aux;
	(*head)->prev = new;
	new->next = *head;
}

void	insertion_last(int n, t_node **head)
{
	t_node	*new;

	new = (t_node *) malloc(sizeof(t_node));
	new->philo_id = n;
	new->nb_eat = 0;
	new->satisfied=0;
	new->last_meal = 0;
	if (*head == NULL)
		add_first_node(head, new);
	else
		add_node(head, new);
}

void	print_nodes(t_node *head)
{
	t_node	*aux;

	aux = head;
	while (aux->next != head)
	{
		printf("philo_id = %d\n", aux->philo_id);
		aux = aux->next;
	}
	printf("philo_id = %d\n", aux->philo_id);
}

void	del_node(t_node **head)
{
	t_node	*temp;

	if ((*head)->next == *head)
	{
		free(*head);
		*head = NULL;
		return ;
	}
	temp = *head;
	while (temp->next != *head)
	{
		temp = temp->next;
	}
	temp->next = (*head)->next;
	(*head)->next->prev = temp;
	free(*head);
	*head = temp->next;
}

void	free_list(t_node **head)
{
	while (*head != NULL)
	{
		del_node(head);
	}
}

//time
long int	current_time()
{
	struct	timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

//simulation

void	*philo_eat(t_node **head)
{
	pthread_mutex_lock(&mutex);
	long time_diff;

	time_diff = (current_time() - (*head)->data->start_time) / 1000;
	printf("%ld philo %d is eating\n", time_diff, (*head)->philo_id);
	(*head)->last_meal = time_diff;
	(*head)->nb_eat++;
	usleep(150 * 1000);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

void	*philo_sleep(t_node *head)
{
	long time_diff;

	time_diff = (current_time() - head->data->start_time) / 1000;
	printf("%ld philo %d is sleeping\n", time_diff, head->philo_id);
	usleep(100 * 1000);
	return (NULL);
}

void	*philo_think(t_node *head)
{
	long time_diff;

	time_diff = (current_time() - head->data->start_time) / 1000;
	printf("%ld philo %d is thinking\n", time_diff, head->philo_id);
	return (NULL);
}

void	*routine(void *arg)
{
	t_node	*head;

	head = (t_node*)arg;
	while (1)
	{
		//printf("flag_satisfied: %d\n", head->data->all_satisfied);
		if (head->data->all_satisfied || head->data->died)
			break;
		if (!head->data->died)
			philo_eat(&head);
		if (!head->data->died)
			philo_sleep(head);
		if (!head->data->died)
			philo_think(head);
	}
	return (NULL);
}

int	everyone_is_satisfied(t_node *head)
{
	t_node	*aux;

	aux = head;
	while (aux->next != head)
	{
		if (aux->satisfied == 0)
			return (0);
		aux = aux->next;
	}
	if (aux->satisfied == 0)
			return (0);
	return (1);
}

void	*monitoring(void *arg)
{
	t_node	*head;
	t_node	*aux;
	int		time_diff;
	long	last_meal_time = 0;

	head = (t_node*)arg;
	aux = head;
	while (1)
	{
		//usleep(20000);
		if (aux->nb_eat == aux->data->must_eat)
		{
			aux->satisfied = 1;
		}
	//	printf("philo_id = %d nb_eat= %d satisfied= %d\n", aux->philo_id, aux->nb_eat, aux->satisfied);
		if (everyone_is_satisfied(head))
		{
			aux->data->all_satisfied = 1;
			//printf("all satisfied\n");
			break;
		}
		//printf("last meal philo %d = %ld\n", aux->philo_id, aux->last_meal);
		time_diff = (current_time() - head->data->start_time) / 1000;
		//printf("%ld\n", time_diff - aux->last_meal);
		if ((time_diff - aux->last_meal) >= aux->data->t_die)
		{
			aux->data->died = 1;
			//printf("%ld\n", time_diff - last_meal_time);
			printf("%d philo %d died\n", time_diff, head->philo_id);
			break;
		}
		aux = aux->next;
	}
	return (NULL);
}

void	create_philos(t_node *head)
{
	t_node	*aux;

	aux = head;
	while (aux->next != head)
	{
		pthread_create(&aux->philo, NULL, &routine, (void *)aux);
		aux = aux->next;
	}
	pthread_create(&aux->philo, NULL, &routine, (void *)aux);
	aux = aux->next;
	pthread_create(&aux->data->monitoring, NULL, &monitoring, (void *)aux);
}

void	join_philos(t_node *head)
{
	t_node	*aux;

	aux = head;
	while (aux->next != head)
	{
		pthread_join(aux->philo, NULL);
		aux = aux->next;
	}
	pthread_join(aux->philo, NULL);
	pthread_join(aux->data->monitoring, NULL);
}

void	fill_node_data(t_node *head, t_data *data)
{
	t_node	*aux;

	aux = head;
	while (aux->next != head)
	{
		aux->data = data;
		aux = aux->next;
	}
	aux->data = data;
}

//main
int	main(int argc, char *argv[])
{
	t_node	*head;
	t_data	data;
	int		i;
	int		nb_nodes;

	i = 1;
	head = NULL;
	pthread_mutex_init(&mutex, NULL);
	nb_nodes = atoi(argv[1]);
	while (i <= nb_nodes)
	{
		insertion_last(i, &head);
		i++;
	}
	data.start_time = current_time();
	data.must_eat = 2;
	data.nb_philos = nb_nodes;
	data.t_die = 1000;
	data.died = 0;
	data.all_satisfied = 0;
	fill_node_data(head, &data);
	create_philos(head);
	join_philos(head);
	free_list(&head);
	return(0);
}
