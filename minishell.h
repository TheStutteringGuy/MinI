/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:17:56 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/27 14:11:28 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "Exec/Libft/libft.h"
#include "Exec/get_next_line/get_next_line.h"
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
#include <limits.h>

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

typedef struct s_pipe
{
    int size;
    int **pipes;
    pid_t *pid_list;
} t_pipe;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

extern int last_exit_status;

// the enum used for the lexer and tokenization
typedef enum s_type
{
    COMMAND,
    ARGUMENT,
    PIPE,
    RED_IN,
    RED_OUT,
    APPEND,
    HERDOC
} t_type;

// struct for the tokens
typedef struct s_token
{
    t_type type;
    char *value;
    struct s_token *next;
} t_token;

// Struct for both output and input
typedef struct s_output_input
{
    int ambigious;
    int whichis;
    char *filename;
    int append; // 0 if normal redirection, 1 if append
    int heredoc;
    char *delimiter;
    int delimiter_expand;
    char *heredoc_file; // where im gonna put the file name 
    struct s_output_input *next;
} t_output_input;

// main struct
typedef struct s_cmd
{
    char *command;
    char **arguments;
    t_output_input *redirection;
    struct s_cmd *next;
} t_cmd;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char *ft_strdup(const char *s);
size_t ft_strlen(const char *s);
char **ft_split(char const *s, char c);
int ft_strcmp(char *s1, char *s2);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
char *ft_strcpy(char *dest, const char *src);
char *ft_strncpy(char *dest, const char *src, size_t n);
bool ft_isspace(int c);
void *ft_memset(void *s, int c, size_t n);
char *ft_itoa(int n);
int ft_isdigit(int c);
char *ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);

// lexer includes
t_token *create_token(t_type type, char *value);
void add_token(t_token **head, t_token *new_token);
t_type classify_token(char *token, t_type expected);
void handle_token(t_token **token_list, char *token, t_type *expected);
void tokenize_input(char *input, t_token **token_list);
int is_multi_operator(char *str);
int is_operator(char c);

// parser includes
t_cmd *create_new_command(t_token *token);
void add_argument_to_command(t_cmd *current_cmd, t_token *token);
void handle_redirections(t_cmd *current_cmd, t_token **current_token, t_exec *exec);
void process_token(t_cmd **cmd_list, t_cmd **current_cmd, t_token **current_token, t_type *expected, t_exec *exec);
t_cmd *parse_tokens(t_token *token_list, t_exec *exec);
void process_redirection_or_pipe(t_cmd **cmd_list, t_cmd **current_cmd, t_token **current_token, t_type *expected, t_exec *exec);
void process_command_or_argument(t_cmd **cmd_list, t_cmd **current_cmd, t_token **current_token, t_type *expected, t_exec *exec);
t_cmd *create_empty_command(void);
char *expand_herdoc(char *str);
void ft_error(char *s1);

// print include
void print_commands(t_cmd *cmd_list);

// free resources
void free_tokens(t_token *token_list);
// void free_token(char **tokens);
//  void free_input_files(t_input_file *input_list);
//  void free_output_files(t_output_file *output_list);
void free_commands(t_cmd *cmd_list);

// quotes includes
int check_syntax_errors(t_token *token_list);
char *remove_quotes(char *token, t_exec *exec);
char *handle_incorrect_quotes(char *token);
char *trim_spaces(char *str);
char *remove_delimiter_quotes(t_output_input *new, char *str);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
int ft_get_export(t_linked *list, char *name);
char *ft_getexport(t_linked *list, char *name);
void copy_environ(t_linked **list, t_linked *environ);
int list_size(t_linked *list);
void print_error(char *s1, char *s2, char *s3, int value);
long    ft_atol(char *str);
int    handle_heredoc(t_exec *data, t_cmd **input);
int    ft_atoui(char *str);

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
