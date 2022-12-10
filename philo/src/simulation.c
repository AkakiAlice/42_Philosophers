/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:11:54 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/10 15:32:45 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	hold_forks(t_node *head)
{

	/*if (head->philo_id % 2 == 0)
		usleep(1000);
	if (head->philo_id != head->rules->nb_philos)
	{
		pthread_mutex_lock(&head->fork);
	//	print_status(head, FORK);
		pthread_mutex_lock(&head->next->fork);
	//	print_status(head, FORK);
	}
	else
	{
		pthread_mutex_lock(&head->next->fork);
		//print_status(head, FORK);
		pthread_mutex_lock(&head->fork);
		//print_status(head, FORK);
	}*/
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
	if (!read_var(&(*head)->data->died_flag, &(*head)->data->mutex_var))
	{
		time_diff = (current_time() - (*head)->data->start_time) / 1000;
		print_status(*head, EAT);
		pthread_mutex_lock(&(*head)->mutex_last_meal);
		(*head)->last_meal = time_diff;
		pthread_mutex_unlock(&(*head)->mutex_last_meal);
		pthread_mutex_lock(&(*head)->mutex_nb_eat);
		(*head)->nb_eat++;
		//write_var(&(*head)->last_meal, time_diff, &(*head)->data->mutex_var);
		//write_var(&(*head)->nb_eat, (*head)->nb_eat+1, &(*head)->data->mutex_var);
		pthread_mutex_unlock(&(*head)->mutex_nb_eat);
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

void	*routine(void *arg)
{
	t_node	*head;

	head = (t_node *)arg;
	while (1)
	{
		if (read_var(&head->data->all_satisfied_flag, &head->data->mutex_var) || read_var(&head->data->died_flag, &head->data->mutex_var))
			break ;
		if (!read_var(&head->data->died_flag, &head->data->mutex_var))
			philo_eat(&head);
		if (!read_var(&head->data->died_flag, &head->data->mutex_var))
			philo_sleep(head);
		if (!read_var(&head->data->died_flag, &head->data->mutex_var))
			philo_think(head);
	}
	return (NULL);
}
