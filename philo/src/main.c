/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:18:43 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/11 11:21:24 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutex_list(t_node *head)
{
	t_node	*aux;

	aux = head;
	while (aux->next != head)
	{
		pthread_mutex_destroy(&aux->fork);
		pthread_mutex_destroy(&aux->mutex_last_meal);
		pthread_mutex_destroy(&aux->mutex_nb_eat);
		aux = aux->next;
	}
	pthread_mutex_destroy(&aux->fork);
	pthread_mutex_destroy(&aux->mutex_last_meal);
	pthread_mutex_destroy(&aux->mutex_nb_eat);
}

void	destroy_mutex(t_node *head)
{
	pthread_mutex_destroy(&head->data->mutex_print);
	pthread_mutex_destroy(&head->data->mutex_satisfied_flag);
	pthread_mutex_destroy(&head->data->mutex_died_flag);
	destroy_mutex_list(head);
}

int	main(int argc, char *argv[])
{
	t_node	*head;

	head = NULL;
	if (!check_args(argc, argv))
		return (1);
	create_linked_list(argv, &head);
	init(argc, argv, head);
	create_philos(head);
	join_philos(head);
	destroy_mutex(head);
	free(head->data);
	free(head->rules);
	free_list(&head);
	return (0);
}
