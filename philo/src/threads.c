/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:08:33 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/08 16:02:08 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
