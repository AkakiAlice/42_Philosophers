/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:39:13 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/13 17:31:00 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_error_msg(char *msg)
{
	write(2, RED, ft_strlen(RED));
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, RESET, ft_strlen(RESET));
}

void	print_status(t_node *head, int status)
{
	long int	time_diff;

	pthread_mutex_lock(&head->data->mutex_print);
	if (!read_var(&head->data->all_satisfied_flag, &head->data->finish_flag)
		&& !read_var(&head->data->died_flag, &head->data->mutex_died_flag))
	{
		time_diff = (current_time() - head->data->start_time);
		if (status == EAT)
			printf ("%ld philo %d is eating\n", time_diff, head->philo_id);
		if (status == SLEEP)
			printf("%ld philo %d is sleeping\n", time_diff, head->philo_id);
		if (status == THINK)
			printf("%ld philo %d is thinking\n", time_diff, head->philo_id);
		if (status == FORK)
			printf("%ld philo %d has taken a fork\n",
				time_diff, head->philo_id);
	}
	pthread_mutex_unlock(&head->data->mutex_print);
}

void	write_var(long int *var, long int status, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*var = status;
	pthread_mutex_unlock(mutex);
}

int	read_var(long int *var, pthread_mutex_t *mutex)
{
	long int	temp;

	pthread_mutex_lock(mutex);
	temp = *var;
	pthread_mutex_unlock(mutex);
	return (temp);
}
