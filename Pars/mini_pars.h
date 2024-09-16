#ifndef MINI_PARS_H
#define MINI_PARS_H

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
#include "../Exec/Libft/libft.h"

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
    HERDOC,
    ENV
} t_type;

// struct for the tokens
typedef struct s_token
{
    t_type type;
    char *value;
    struct s_token *next;
} t_token;

// struct for the ouput files
typedef struct s_output_file
{
    char *filename;
    int append; // 0 if normal redirection, 1 if append
    struct s_output_file *next;
} t_output_file;

// struct for the input files
typedef struct s_input_file
{
    int heredoc;
    char *delimiter;
    char *filename;
    struct s_input_file *next;
} t_input_file;

// main struct
typedef struct s_cmd
{
    char *command;
    char **arguments;
    int *last_exit_status;
    t_input_file *input_files;   // Linked list of input files
    t_output_file *output_files; // Linked list of output files
    struct s_cmd *next;
} t_cmd;

// includ protypes
char *ft_strdup(const char *s);
size_t ft_strlen(const char *s);
char **ft_split(char const *s, char c);
int ft_strcmp(char *s1, char *s2);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
char *ft_strcpy(char *dest, const char *src);
char *ft_strncpy(char *dest, const char *src, size_t n);
bool ft_isspace(int c);
void *ft_memset(void *s, int c, size_t n);
char	*ft_itoa(int n);

// lexer includes
t_token *create_token(t_type type, char *value);
void add_token(t_token **head, t_token *new_token);
t_type classify_token(char *token, t_type expected);
void handle_token(t_token **token_list, char *token, t_type *expected);
void tokenize_input(char *input, t_token **token_list);
void add_input_file(t_input_file **input_list, char *filename, int heredoc, char *delimiter);
void add_output_file(t_output_file **output_list, char *filename, int append);

// parser includes
t_cmd *create_new_command(t_token *token);
void add_argument_to_command(t_cmd *current_cmd, t_token *token);
void handle_redirections(t_cmd *current_cmd, t_token **current_token);
void process_token(t_cmd **cmd_list, t_cmd **current_cmd, t_token **current_token, t_type *expected);
t_cmd *parse_tokens(t_token *token_list);
void process_redirection_or_pipe(t_cmd **cmd_list, t_cmd **current_cmd, t_token **current_token, t_type *expected);
void process_command_or_argument(t_cmd **cmd_list, t_cmd **current_cmd, t_token **current_token, t_type *expected);
t_cmd *create_empty_command(void);

// print include
void print_commands(t_cmd *cmd_list);

// free resources
void free_tokens(t_token *token_list);
void free_token(char **tokens);
void free_input_files(t_input_file *input_list);
void free_output_files(t_output_file *output_list);
void free_commands(t_cmd *cmd_list);

// quotes includes
int check_syntax_errors(t_token *token_list);
char *remove_quotes(char *token);
char *handle_incorrect_quotes(char *token);

// env includes
char *expand_env_var(char *token);

#endif