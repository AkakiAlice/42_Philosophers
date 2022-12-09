/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:18:43 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/09 17:31:07 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	/*pthread_mutex_destroy(&head->data->mutex_eat);
	pthread_mutex_destroy(&head->data->mutex_print);
	pthread_mutex_destroy(&head->data->mutex_read_var);
	pthread_mutex_destroy(&head->data->mutex_write_var);*/
	free(head->data);
	free(head->rules);
	free_list(&head);
	return (0);
}
