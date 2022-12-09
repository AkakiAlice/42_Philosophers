/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:11:54 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/08 18:47:04 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_eat(t_node **head)
{
	pthread_mutex_lock(&(*head)->data->mutex_eat);
	long time_diff;

	time_diff = (current_time() - (*head)->data->start_time) / 1000;
	print_status(*head, EAT);
	//printf("%ld philo %d is eating\n", time_diff, (*head)->philo_id);
	(*head)->last_meal = time_diff;
	(*head)->nb_eat++;
	usleep((*head)->rules->time_to_eat * 1000);
	pthread_mutex_unlock(&(*head)->data->mutex_eat);
	return (NULL);
}

void	*philo_sleep(t_node *head)
{
	//long time_diff;

	//time_diff = (current_time() - head->data->start_time) / 1000;
	//printf("%ld philo %d is sleeping\n", time_diff, head->philo_id);
	print_status(head, SLEEP);
	usleep(head->rules->time_to_sleep * 1000);
	return (NULL);
}

void	*philo_think(t_node *head)
{
	//long time_diff;

//	time_diff = (current_time() - head->data->start_time) / 1000;
	//printf("%ld philo %d is thinking\n", time_diff, head->philo_id);
	print_status(head, THINK);
	return (NULL);
}

void	*routine(void *arg)
{
	t_node	*head;

	head = (t_node*)arg;
	while (1)
	{
		if (head->data->all_satisfied_flag || head->data->died_flag)
			break;
		if (!head->data->died_flag)
			philo_eat(&head);
		if (!head->data->died_flag)
			philo_sleep(head);
		if (!head->data->died_flag)
			philo_think(head);
	}
	return (NULL);
}
