/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:18:43 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/08 10:13:24 by alida-si         ###   ########.fr       */
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
	printf("td crt\n");
	print_nodes(head);
	free_list(&head);
	return (0);
}
