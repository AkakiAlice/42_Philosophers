/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:13:05 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/09 18:25:04 by alida-si         ###   ########.fr       */
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

void	*monitoring(void *arg)
{
	t_node	*head;
	t_node	*aux;
	int		time_diff;

	head = (t_node *)arg;
	aux = head;
	while (1)
	{
		if (read_var(&aux->nb_eat, &aux->data->mutex_read_var) == read_var(&aux->rules->must_eat, &aux->data->mutex_read_var) && read_var(&aux->rules->must_eat, &aux->data->mutex_read_var) != 0)
		{
			aux->satisfied = 1;
		}
		if (everyone_is_satisfied(head))
		{
			//aux->data->all_satisfied_flag = 1;
			write_var(&aux->data->all_satisfied_flag, 1, &aux->data->mutex_write_var);
			break ;
		}
		time_diff = (current_time() - head->data->start_time) / 1000;
		if ((time_diff - read_var((int *)&aux->last_meal, &aux->data->mutex_read_var)) >= read_var(&aux->rules->time_to_die, &aux->data->mutex_read_var))
		{
			//aux->data->died_flag = 1;
			write_var(&aux->data->died_flag, 1, &aux->data->mutex_write_var);
			printf("%d philo %d died\n", time_diff, head->philo_id);
			break ;
		}
		aux = aux->next;
	}
	return (NULL);
}
