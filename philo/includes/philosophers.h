/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:39:24 by alida-si          #+#    #+#             */
/*   Updated: 2022/11/25 13:15:47 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Colors
# define RED "\033[38;2;222;56;43m"
# define BLUE "\033[38;2;34;183;235m"
# define CYAN "\033[0;96m"
# define RESET "\033[0m"

//check_input.c
int			check_args(int argc, char **argv);

//utils.c
void		print_error_msg(char *msg);
size_t		ft_strlen(const char *s);
long int	ft_atoll(const char *str);
char		*ft_strcat(char *s1, char *s2);
int			ft_isdigit(int c);

#endif
