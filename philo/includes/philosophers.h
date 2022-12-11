/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:39:24 by alida-si          #+#    #+#             */
/*   Updated: 2022/12/10 18:15:41 by alida-si         ###   ########.fr       */
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
	long int		start_time;
	pthread_t		monitoring;
	long int		all_satisfied_flag;
	long int		died_flag;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_satisfied_flag;
	pthread_mutex_t	mutex_died_flag;
}			t_data;

typedef struct s_rules
{
	int			nb_philos;
	long int	time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	long int	must_eat;
}			t_rules;

typedef struct s_node
{
	struct s_node	*prev;
	struct s_node	*next;
	int				philo_id;
	long int		nb_eat;
	int				satisfied;
	long int		last_meal;
	pthread_mutex_t	fork;
	pthread_mutex_t	mutex_last_meal;
	pthread_mutex_t	mutex_nb_eat;
	pthread_t		philo;
	t_data			*data;
	t_rules			*rules;
}			t_node;

//colors
# define RED "\033[38;2;222;56;43m"
# define BLUE "\033[38;2;34;183;235m"
# define CYAN "\033[0;96m"
# define RESET "\033[0m"

//print status
# define EAT 1
# define SLEEP 2
# define THINK 3
# define FORK 4

//check_input.c
int			check_args(int argc, char **argv);

//init.c
void		init(int argc, char *argv[], t_node *head);

//linked_list.c
void		create_linked_list(char *argv[], t_node **head);

//routines.c
void		*monitoring(void *arg);
void		*routine(void *arg);

//actions.c
void		*philo_think(t_node *head);
void		*philo_sleep(t_node *head);
void		*philo_eat(t_node **head);

//threads.c
void		join_philos(t_node *head);
void		create_philos(t_node *head);

//time.c
long int	current_time(void);

//utils_linked_list.c
void		free_list(t_node **head);

//utils.c
int			ft_atoi(const char *str);
void		print_error_msg(char *msg);
size_t		ft_strlen(const char *s);
long int	ft_atoll(const char *str);
char		*ft_strcat(char *s1, char *s2);
int			ft_isdigit(int c);
void		print_status(t_node *head, int status);
void		write_var(long int *var, long int status, pthread_mutex_t *mutex);
int			read_var(long int *var, pthread_mutex_t *mutex);

#endif
