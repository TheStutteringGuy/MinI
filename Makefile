# BASIC SETTINGS :

CC = cc
CFLAGS = -Wall -Wextra -Werror -w -g #-fsanitize=address
RM = rm -rf

###########################################################################################

# KatyCat Srcs :

SRCS_Pars = Pars/*.c Pars/lexer/*.c Pars/parse/*.c

###########################################################################################

# TheStutteringGUy Srcs:

SRCS_Exec = Exec/*.c Exec/get_next_line/*.c Exec/builtins/*.c

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
