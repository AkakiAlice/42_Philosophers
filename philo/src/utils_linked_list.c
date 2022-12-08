/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:10:26 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/08 12:03:41 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_nodes(t_node *head)
{
	t_node	*aux;

	aux = head;
	while (aux->next != head)
	{
		printf("philo_id = %d | t_eat = %d | t_sleep = %d | m_eat = %d\n", aux->philo_id, aux->rules->time_to_eat, aux->rules->time_to_sleep, aux->rules->must_eat);
		aux = aux->next;
	}
	printf("philo_id = %d | t_eat = %d | t_sleep = %d | m_eat = %d\n", aux->philo_id, aux->rules->time_to_eat, aux->rules->time_to_sleep, aux->rules->must_eat);
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
