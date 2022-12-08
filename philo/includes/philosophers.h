/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:39:24 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/08 11:01:12 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data
{
	long		start_time;
	pthread_t	monitoring;
	int			all_satisfied_flag;
	int			died_flag;
}			t_data;

typedef struct s_rules
{
	int	nb_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}			t_rules;

typedef struct s_node
{
	struct s_node	*prev;
	struct s_node	*next;
	int				philo_id;
	int				nb_eat;
	int				satisfied;
	long			last_meal;
	pthread_t		philo;
	t_data			*data;
	t_rules			*rules;
}			t_node;

// Colors
# define RED "\033[38;2;222;56;43m"
# define BLUE "\033[38;2;34;183;235m"
# define CYAN "\033[0;96m"
# define RESET "\033[0m"

//check_input.c
int			check_args(int argc, char **argv);

//linked_list.c
void		create_linked_list(char *argv[], t_node **head);

//utils_linked_list.c
void		free_list(t_node **head);
void		print_nodes(t_node *head);

//utils.c
int			ft_atoi(const char *str);
void		print_error_msg(char *msg);
size_t		ft_strlen(const char *s);
long int	ft_atoll(const char *str);
char		*ft_strcat(char *s1, char *s2);
int			ft_isdigit(int c);

#endif
