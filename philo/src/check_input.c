/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:37:24 by alida-si          #+#    #+#             */
/*   Updated: 2022/11/23 18:44:22 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_number_of_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		print_error_msg("Invalid number of arguments\n");
		return (0);
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (!check_number_of_args(argc))
		return (0);
	(void)argv;
	return (1);
}
