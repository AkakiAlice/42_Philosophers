/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:39:13 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/10 11:06:28 by alida-si         ###   ########.fr       */
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

void	print_error_msg(char *msg)
{
	write(2, RED, ft_strlen(RED));
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, RESET, ft_strlen(RESET));
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

void	print_status(t_node *head, int status)
{
	long int	time_diff;

	pthread_mutex_lock(&head->data->mutex_print);
	time_diff = (current_time() - head->data->start_time) / 1000;
	if (!read_var(&head->data->all_satisfied_flag, &head->data->mutex_var) && !read_var(&head->data->died_flag, &head->data->mutex_var))
	{
		if (status == EAT)
			printf ("%ld philo %d is eating\n", time_diff, head->philo_id);
		else if (status == SLEEP)
			printf("%ld philo %d is sleeping\n", time_diff, head->philo_id);
		else if (status == THINK)
			printf("%ld philo %d is thinking\n", time_diff, head->philo_id);
		else if (status == FORK)
			printf("%ld philo %d has taken a fork\n", time_diff, head->philo_id);
	}
	pthread_mutex_unlock(&head->data->mutex_print);
}

void	write_var(long int *var, long int status, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*var = status;
	pthread_mutex_unlock(mutex);
}

int	read_var(long int *var, pthread_mutex_t *mutex)
{
	long int	temp;

	pthread_mutex_lock(mutex);
	temp = *var;
	pthread_mutex_unlock(mutex);
	return (temp);
}
