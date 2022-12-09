/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:37:24 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/09 17:42:12 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	add_first_node(t_node **head, t_node *new)
{
	*head = new;
	new->next = *head;
	new->prev = *head;
}

void	add_node(t_node **head, t_node *new)
{
	t_node	*aux;

	aux = *head;
	while (aux->next != *head)
	{
		aux = aux->next;
	}
	aux->next = new;
	new->prev = aux;
	(*head)->prev = new;
	new->next = *head;
}

void	fill_new_node(int n, t_node *new)
{
	new->philo_id = n;
	new->nb_eat = 0;
	new->satisfied = 0;
	new->last_meal = 0;
	pthread_mutex_init(&new->fork, NULL);
}

void	insertion_last(int n, t_node **head)
{
	t_node	*new;

	new = (t_node *) malloc(sizeof(t_node));
	fill_new_node(n, new);
	if (*head == NULL)
		add_first_node(head, new);
	else
		add_node(head, new);
}

void	create_linked_list(char *argv[], t_node **head)
{
	int	i;
	int	nb_philos;

	i = 1;
	nb_philos = ft_atoi(argv[1]);
	while (i <= nb_philos)
	{
		insertion_last(i, head);
		i++;
	}
}
