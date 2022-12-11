/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:11:54 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/11 14:23:47 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	hold_forks(t_node *head)
{
	if (head->philo_id != head->rules->nb_philos
		|| head->rules->nb_philos % 2 != 0)
	{
		pthread_mutex_lock(&head->fork);
		pthread_mutex_lock(&head->next->fork);
	}
	else
	{
		pthread_mutex_lock(&head->next->fork);
		pthread_mutex_lock(&head->fork);
	}
	print_status(head, FORK);
	print_status(head, FORK);
}

void	drop_forks(t_node *node)
{
	pthread_mutex_unlock(&node->fork);
	pthread_mutex_unlock(&node->next->fork);
}

void	*philo_eat(t_node **head)
{
	long	time_diff;

	hold_forks(*head);
	if (!read_var(&(*head)->data->died_flag, &(*head)->data->mutex_died_flag))
	{
		time_diff = (current_time() - (*head)->data->start_time) / 1000;
		print_status(*head, EAT);
		write_var(&(*head)->last_meal, time_diff, &(*head)->mutex_last_meal);
		write_var(&(*head)->nb_eat, (*head)->nb_eat + 1,
			&(*head)->mutex_nb_eat);
		usleep((*head)->rules->time_to_eat * 1000);
	}
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
