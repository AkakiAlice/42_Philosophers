/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:37:24 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/08 10:15:56 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_isdigit(char *argv)
{
	int	j;

	j = 0;
	while (argv[j])
	{
		if (argv[j] == '-' || argv[j] == '+')
			j++;
		if (!ft_isdigit(argv[j]))
		{
			printf("%sPlease make sure to insert just numeric characters\n%s",
				CYAN, RESET);
			return (0);
		}
		j++;
	}
	return (1);
}

int	check_value_min_max(char *argv)
{
	if (ft_atoll(argv) <= 0 || ft_atoll(argv) > 2147483647)
		return (0);
	return (1);
}

int	check_is_int(char **argv)
{
	int		i;
	char	*str;
	char	*error_msg;

	str = ": all arguments must be integers between one and INT_MAX\n";
	error_msg = NULL;
	i = 1;
	while (argv[i])
	{
		if (!check_isdigit(argv[i]) || !check_value_min_max(argv[i]))
		{
			error_msg = ft_strcat(argv[i], str);
			print_error_msg(error_msg);
			free(error_msg);
			return (0);
		}
		i++;
	}
	return (1);
}

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
	if (!check_is_int(argv))
		return (0);
	return (1);
}
