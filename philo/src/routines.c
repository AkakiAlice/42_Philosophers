/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:13:05 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/13 17:29:12 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	check_death(t_node *node)
{
	int		time_diff;

	time_diff = (current_time() - node->data->start_time);
	if ((time_diff - read_var(&node->last_meal, &node->mutex_last_meal))
		>= node->rules->time_to_die)
	{
		pthread_mutex_lock(&node->data->mutex_died_flag);
		node->data->died_flag = 1;
		printf("%d philo %d died\n", time_diff, node->philo_id);
		pthread_mutex_unlock(&node->data->mutex_died_flag);
		return (1);
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_node	*head;
	t_node	*aux;

	head = (t_node *)arg;
	aux = head;
	while (1)
	{
		usleep(100);
		if (check_death(aux))
			break ;
		if (read_var(&aux->nb_eat, &aux->mutex_nb_eat) == aux->rules->must_eat
			&& aux->rules->must_eat != 0)
		{
			aux->satisfied = 1;
		}
		if (everyone_is_satisfied(head))
		{
			write_var(&aux->data->all_satisfied_flag, 1,
				&aux->data->finish_flag);
			break ;
		}
		aux = aux->next;
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_node	*head;

	head = (t_node *)arg;
	if (head->philo_id % 2 == 0)
		usleep(300);
	while (1)
	{
		if (read_var(&head->data->all_satisfied_flag, &head->data->finish_flag)
			|| read_var(&head->data->died_flag, &head->data->mutex_died_flag))
			break ;
		if (!read_var(&head->data->died_flag, &head->data->mutex_died_flag))
			philo_eat(&head);
		if (!read_var(&head->data->died_flag, &head->data->mutex_died_flag))
			philo_sleep(head);
		if (!read_var(&head->data->died_flag, &head->data->mutex_died_flag))
			philo_think(head);
	}
	return (NULL);
}
