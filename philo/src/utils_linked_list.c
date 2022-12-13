/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:10:26 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/13 17:30:45 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
