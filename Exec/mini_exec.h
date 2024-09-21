/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:51:10 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/21 02:03:34 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_EXEC_H
#define MINI_EXEC_H

#include <stdio.h>
#include "Libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

#define PATH_MAX 4096
#define TRUE 1

// STRUCTS :

typedef struct s_linked
{
	char *key;
	char *value;
	struct s_linked *next;
} t_linked;

typedef struct s_exec
{
	t_linked *environ;
	t_linked *export;
	char **envp;
	char **arg;
} t_exec;

// PROTOTYPES :

void handle_sig(void);
const char *prompt(char *prompt_char);
void env_list(t_linked **list, char **envp);
void exec(t_exec *data, t_cmd *input);
void execve_handle_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd);
void create_node(t_linked **list, char *key, char *value,
				 int flag);
void clear_list(t_linked **list);
void remove_list(t_linked **list, char *key);
char *ft_getenv(t_linked *list, char *name);
void copy_environ(t_linked **list, t_linked *environ);
int ft_get_export(t_linked *list, char *name);
int list_size(t_linked *list);
void    print_error(char *s1, char *s2, char *s3, int value)

// BUILTINS :

void pwd_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd);
void env_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd);
void echo_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd);
void cd_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd);
void exit_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd);
void export_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd);
void unset_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd);

// BUILTINS HARD :

void pwd_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd);
void env_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd);
void echo_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd);
void cd_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd);
void exit_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd);
void export_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd);
void unset_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd);
void execve_handle_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd);

#endif
