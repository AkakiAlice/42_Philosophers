/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:55:45 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/10 16:57:18 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	index;
	int	result;
	int	sign;

	index = 0;
	sign = 1;
	result = 0;
	while (str[index] == ' ' || (str[index] >= '\t' && str[index] <= '\r'))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign *= -1;
		index++;
	}
	while (ft_isdigit(str[index]))
	{
		result = (str[index] - '0') + (result * 10);
		index++;
	}
	return (result * sign);
}

long int	ft_atoll(const char *str)
{
	long int	index;
	long int	result;
	long int	sign;

	index = 0;
	sign = 1;
	result = 0;
	while (str[index] == ' ' || (str[index] >= '\t' && str[index] <= '\r'))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign *= -1;
		index++;
	}
	while (ft_isdigit(str[index]))
	{
		result = (str[index] - '0') + (result * 10);
		index++;
	}
	return (result * sign);
}

char	*ft_strcat(char *s1, char *s2)
{
	size_t	i;
	size_t	len;
	char	*result;

	len = (ft_strlen(s1) + ft_strlen(s2));
	result = (char *)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (*s1)
	{
		result[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		result[i] = *s2;
		s2++;
		i++;
	}
	result[i] = '\0';
	return (result);
}
