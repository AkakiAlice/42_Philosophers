/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:08:33 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/09 17:23:01 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine_one_philo(void *arg)
{
	t_node	*head;

	head = (t_node *)arg;
	print_status(head, FORK);
	return (NULL);
}

void	create_philos(t_node *head)
{
	t_node	*aux;

	head->data->start_time = current_time();
	aux = head;
	if (head->rules->nb_philos == 1)
		pthread_create(&aux->philo, NULL, &routine_one_philo, (void *)aux);
	else
	{
		while (aux->next != head)
		{
			pthread_create(&aux->philo, NULL, &routine, (void *)aux);
			aux = aux->next;
		}
		pthread_create(&aux->philo, NULL, &routine, (void *)aux);
		aux = aux->next;
	}
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
