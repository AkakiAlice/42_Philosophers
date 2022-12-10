# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 18:11:37 by alida-si          #+#    #+#              #
#    Updated: 2022/12/10 18:11:03 by alida-si         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


## COLORS ##

DEFAULT		=	\e[39m
MAGENTA		=	\e[95m
CYAN		=	\e[96m

# **************************************************************************** #

NAME = philo

# LIBRARY #

HEADER = -I includes

# COMPILATION #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread #-g -fsanitize=thread

# DELETE #

RM = rm -rf

# DIRECTORIES #

SRC_DIR = ./src/
VPATH := $(SRC_DIR)

# FILES #

FILES = main.c\
		utils.c\
		linked_list.c\
		utils_linked_list.c\
		init.c\
		time.c\
		threads.c\
		routines.c\
		actions.c\
		utils_libft.c\
		check_input.c

# COMPILED_SOURCES #

OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(notdir $(FILES:.c=.o)))

# **************************************************************************** #

## RULES ##

$(OBJ_DIR)%.o: %.c
		@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
		@echo "\n$(CYAN)----------------------------------------"
		@echo "------------ MAKE MINISHELL ------------"
		@echo "----------------------------------------\n$(DEFAULT)"
		@$(CC) $(CFLAGS) $(OBJS) $(HEADER) -o $(NAME)

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
		@mkdir $(OBJ_DIR)

clean:
		@$(RM) $(OBJ_DIR)

fclean: clean
		@$(RM) $(NAME)
		@echo "\n$(MAGENTA)----------------------------------------"
		@echo "------------- CLEANING DONE ------------"
		@echo "----------------------------------------\n$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re
