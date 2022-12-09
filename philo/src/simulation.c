/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:11:54 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/09 18:28:58 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	hold_forks(t_node *head)
{
	if (head->philo_id % 2 != 0)
	{
		pthread_mutex_lock(&head->fork);
		pthread_mutex_lock(&head->prev->fork);
	}
	else
	{
		usleep(3550);
		pthread_mutex_lock(&head->fork);
		pthread_mutex_lock(&head->prev->fork);
	}
	print_status(head, FORK);
	print_status(head, FORK);
}

void	drop_forks(t_node *node)
{
	pthread_mutex_unlock(&node->fork);
	pthread_mutex_unlock(&node->prev->fork);
}

void	*philo_eat(t_node **head)
{
	long	time_diff;

	hold_forks(*head);
	time_diff = (current_time() - (*head)->data->start_time) / 1000;
	print_status(*head, EAT);
	(*head)->last_meal = time_diff;
	(*head)->nb_eat++;
	usleep((*head)->rules->time_to_eat * 1000);
	drop_forks(*head);
	return (NULL);
}

void	*philo_sleep(t_node *head)
{
	print_status(head, SLEEP);
	usleep(head->rules->time_to_sleep * 1000);
	return (NULL);
}

void	*philo_think(t_node *head)
{
	print_status(head, THINK);
	return (NULL);
}

void	*routine(void *arg)
{
	t_node	*head;

	head = (t_node *)arg;
	while (1)
	{
		if (head->data->all_satisfied_flag || head->data->died_flag)
			break ;
		if (!head->data->died_flag)
			philo_eat(&head);
		if (!head->data->died_flag)
			philo_sleep(head);
		if (!head->data->died_flag)
			philo_think(head);
	}
	return (NULL);
}
