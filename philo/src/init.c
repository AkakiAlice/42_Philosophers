/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:08:26 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/11 14:24:09 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_data(t_data *data)
{
	data->all_satisfied_flag = 0;
	data->died_flag = 0;
	data->start_time = 0;
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->finish_flag, NULL);
	pthread_mutex_init(&data->mutex_died_flag, NULL);
}

void	init_rules(t_rules *rules, int argc, char *argv[])
{
	rules->nb_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->must_eat = ft_atoi(argv[5]);
	else if (argc == 5)
		rules->must_eat = 0;
}

void	fill_node_data(t_node *head, t_data *data, t_rules *rules)
{
	t_node	*aux;

	aux = head;
	while (aux->next != head)
	{
		aux->data = data;
		aux->rules = rules;
		aux = aux->next;
	}
	aux->data = data;
	aux->rules = rules;
}

void	init(int argc, char *argv[], t_node *head)
{
	t_data	*data;
	t_rules	*rules;

	data = (t_data *) malloc(sizeof(t_data));
	rules = (t_rules *) malloc(sizeof(t_rules));
	init_rules(rules, argc, argv);
	init_data(data);
	fill_node_data(head, data, rules);
}
