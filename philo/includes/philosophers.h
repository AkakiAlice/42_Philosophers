/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:39:24 by alida-si          #+#    #+#             */
/*   Updated: 2022/11/23 18:42:19 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

// Colors
# define RED "\033[38;2;222;56;43m"
# define RESET "\033[0m"

int		check_args(int argc, char **argv);
void	print_error_msg(char *msg);

#endif
