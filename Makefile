# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 01:20:40 by aahlaqqa          #+#    #+#              #
#    Updated: 2024/10/13 00:42:10 by aibn-ich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# BASIC SETTINGS :

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3
RM = rm -rf

###########################################################################################

# KatyCat Srcs :

SRCS_Pars = Pars/*.c Pars/lexer/*.c Pars/parse/*.c

###########################################################################################

# TheStutteringGUy Srcs:

SRCS_Exec = Exec/builtins/cd.c Exec/builtins/echo.c Exec/builtins/env.c Exec/builtins/exit.c Exec/builtins/export.c                                                               \
			Exec/builtins_hard/hard_cd.c Exec/builtins_hard/hard_echo.c Exec/builtins_hard/hard_env.c Exec/builtins_hard/hard_exit.c                                               \
			Exec/builtins_hard/hard_export.c Exec/builtins_hard/hard_pwd.c Exec/builtins_hard/hard_unset.c Exec/builtins_helper/cd_helper2.c                                        \
			Exec/builtins_helper/cd_helper.c Exec/builtins_helper/export_4.c Exec/builtins_helper/export_helper2.c Exec/builtins_helper/export_helper3.c                             \
			Exec/builtins_helper/export_helper.c Exec/builtins/pwd.c Exec/builtins/unset.c Exec/error_handle.c Exec/exec/exec.c Exec/exec/exec_.c Exec/exec/exec_handle.c             \
  			Exec/exec/exec_list2.c Exec/exec/exec_list.c Exec/exec/fd_.c Exec/exec/hard.c Exec/exec/hard_simple_help2.c Exec/exec/hard_simple_help.c Exec/exec/simple.c Exec/ft_atol.c \
   			Exec/ft_atoui.c Exec/get_next_line/get_next_line.c Exec/get_next_line/get_next_line_utils.c Exec/handle_heredoc2.c Exec/handle_heredoc.c Exec/handle_sig.c Exec/list_ft2.c  \
    		Exec/list_ft3.c Exec/list_ft.c Exec/update_.c Exec/update_shlvl.c																											 \

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
