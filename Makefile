# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 01:20:40 by aahlaqqa          #+#    #+#              #
#    Updated: 2024/10/03 17:22:50 by thestutteri      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# BASIC SETTINGS :

CC = cc
CFLAGS = -Wall -Wextra -Werror -w #-fsanitize=address -g3
RM = rm -rf

###########################################################################################

# KatyCat Srcs :

SRCS_Pars = Pars/*.c Pars/lexer/*.c Pars/parse/*.c

###########################################################################################

# TheStutteringGUy Srcs:

SRCS_Exec = Exec/*.c Exec/get_next_line/*.c Exec/builtins/*.c Exec/builtins_hard/*.c

FLAGS = -L Exec/Libft -lft

###########################################################################################


# PHILO SETTINGS :

NFLAGS = -lreadline -lncurses
NAME = minishell

all: $(NAME)

$(NAME): $(SRCS_Exec) $(SRCS_Pars)
	$(CC) $(CFLAGS) main.c $(SRCS_Pars) $(SRCS_Exec) $(NFLAGS) $(FLAGS) -o $(NAME)

clean:

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
