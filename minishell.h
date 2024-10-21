/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:17:56 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/21 23:18:44 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Exec/Libft/libft.h"
# include "Exec/get_next_line/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

# define TRUE 1

extern int					g_last_exit_status;

// STRUCTS :

typedef struct s_linked
{
	char					*key;
	char					*value;
	int						flag;
	struct s_linked			*next;
}							t_linked;

typedef struct s_exec
{
	t_linked				*environ;
	t_linked				*export;
	char					**envp;
	char					**arg;
	int						flag;
	int						delimiter;
	int						quote;
	int						expand;
	int						not;
	int						eof;
	int						s_d;
	int						is_in;
}							t_exec;

typedef struct s_pipe
{
	int						size;
	int						**pipes;
	pid_t					*pid_list;
}							t_pipe;

typedef struct s_norminette
{
	int						i;
	int						j;
	int						y;
	int						z;
	char					*key;
}							t_norminette;

//////////////////////////////////////

# define CHUNK_SIZE 256

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
}							t_type;

// struct for the tokens
typedef struct s_token
{
	t_type					type;
	char					*value;
	struct s_token			*next;
}							t_token;

// Struct for both output and input
typedef struct s_output_input
{
	int						ambigious;
	int						whichis;
	char					*filename;
	int						append;
	int						heredoc;
	char					*delimiter;
	int						delimiter_expand;
	char					*heredoc_file;
	struct s_output_input	*next;
}							t_output_input;

typedef struct s_redirection_flags
{
	int						heredoc;
	int						append;
	int						value;
}							t_redirection_flags;

typedef struct s_redirection_params
{
	char					*filename;
	char					*delimiter;
	t_redirection_flags		flags;
}							t_redirection_params;

// main struct
typedef struct s_cmd
{
	char					*command;
	char					**arguments;
	t_output_input			*redirection;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_cmd_context
{
	t_cmd					**cmd_list;
	t_cmd					**current_cmd;
}							t_cmd_context;

typedef struct s_helpe
{
	int						i;
	int						token_len;
	char					*token;
	int						isoperate;
	char					*res;
	t_type					*expected;
}							t_helpe;

typedef struct s_expansion
{
	char					*res;
	size_t					len;
	size_t					i;
	int						quote_found;
	t_exec					*exec;
}							t_expansion;

typedef struct s_norm
{
	int						i;
	int						j;
	char					*str;
	char					*expanded;
	int						count;
	char					*str1;
}							t_norm;

char						*ft_strdup(const char *s);
size_t						ft_strlen(const char *s);
char						**ft_split(char const *s, char c);
int							ft_strcmp(char *s1, char *s2);
size_t						ft_strlcpy(char *dst, const char *src, size_t size);
char						*ft_strcpy(char *dest, const char *src);
char						*ft_strncpy(char *dest, const char *src, size_t n);
bool						ft_isspace(int c);
void						*ft_memset(void *s, int c, size_t n);
char						*ft_itoa(int n);
int							ft_isdigit(int c);
bool						is_inside_quotes(char *input, int i);
char						*ft_strjoin(char const *s1, char const *s2);
void						*ft_memcpy(void *dest, const void *src, size_t n);
int							is_multi_operator(char *str);
int							is_operator(char c);
t_token						*create_token(t_type type, char *value);
void						add_token(t_token **head, t_token *new_token);
t_type						classify_token(char *token, t_helpe *helpe,
								t_exec *exec);
void						handle_token(t_token **token_list, char *token,
								t_helpe *helpe, t_exec *exec);
void						tokenize_input(char *input, t_token **token_list,
								t_exec *exec);
int							check_for_char(int c);
void						handle_special_case(t_norm *norm);
void						free_helpe(t_helpe *helpe);
void						copy_token(t_token **token_list, t_helpe *helpe,
								t_exec *exec);
void						add_multi_operator(char *token, const char *input,
								int *token_len, int *i);
void						finalize_token(t_token **token_list, t_helpe *helpe,
								t_exec *exec);
void						update_quote(t_exec *exec);
void						append_dollar_and_handle(t_helpe *helpe,
								t_token **token_list, t_exec *exec);
void						handle_dollar_at_end(t_helpe *helpe,
								t_token **token_list, t_exec *exec);
void						handle_result_input(t_helpe *helpe,
								t_token **token_list, t_exec *exec);
void						check_next_characters(char *input, t_helpe *helpe);
int							skip_whitespace(char *input, int i);
void						handle_expansion_result(char *input, t_helpe *helpe,
								t_token **token_list, t_exec *exec);
void						expand_env_var(char *input, t_helpe *helpe,
								t_token **token_list, t_exec *exec);
t_helpe						*initialize_helper(char *input);
void						handle_operators_logic(char *input, t_helpe *helpe,
								t_token **token_list, t_exec *exec);
void						finalize_tokens(t_helpe *helpe,
								t_token **token_list, t_exec *exec);
void						handle_dollar_sign_logic(char *input,
								t_helpe *helpe, t_token **token_list,
								t_exec *exec);
void						initialize_exec(t_exec *exec);
void						handle_exit_status(char *input, t_helpe *helpe,
								t_token **token_list, t_exec *exec);
void						handle_variable_expansion(char *input,
								t_helpe *helpe, t_token **token_list,
								t_exec *exec);
void						handle_dollar_end_case(char *input, t_helpe *helpe,
								t_token **token_list, t_exec *exec);
void						handle_non_empty_result(t_helpe *helpe,
								t_token **token_list, t_exec *exec,
								int is_dollar_at_end);
t_cmd						*create_new_command(t_token *token);
void						add_argument_to_command(t_cmd *current_cmd,
								t_token *token);
void						handle_redirections(t_cmd *current_cmd,
								t_token **current_token, t_exec *exec);
t_cmd						*parse_tokens(t_token *token_list, t_exec *exec);
void						process_command_or_argument(t_cmd_context *cmd_ctx,
								t_token **current_token, t_type *expected,
								t_exec *exec);
void						process_redirection_or_pipe(t_cmd_context *cmd_ctx,
								t_token **current_token, t_type *expected,
								t_exec *exec);
void						process_token(t_cmd_context *cmd_ctx,
								t_token **current_token, t_type *expected,
								t_exec *exec);
t_cmd						*create_empty_command(void);
void						ft_error(char *s1);
char						*expand_herdoc(char *str, t_exec *exec);
void						malloc_error(void);
int							check_quotes(char *input, t_exec *exec);
char						*expand_env_simple(char *input, t_exec *exec);
char						*expand(char *input, t_exec *exec);
t_redirection_params		init_redirection_params(char *filename,
								char *delimiter, t_redirection_flags flags);
void						process_filename(t_output_input *new,
								char *filename, t_exec *exec);
void						process_delimiter(t_output_input *new,
								char *delimiter, t_exec *exec);
void						add_redirection(t_output_input **redirection,
								t_redirection_params *params, t_exec *exec);
t_redirection_flags			initialize_redirection_flags(void);
void						handle_red_in(t_cmd *current_cmd,
								t_token *next_token, t_exec *exec);
void						create_heredoc(t_cmd *current_cmd,
								t_token *next_token, t_exec *exec);
void						handle_red_out(t_cmd *current_cmd,
								t_token *next_token, t_exec *exec);
void						handle_append(t_cmd *current_cmd,
								t_token *next_token, t_exec *exec);
int							process_current_token(t_cmd_context *cmd_ctx,
								t_token **current_token, t_exec *exec,
								t_type *expected);
char						*expand_exit_status(t_expansion *exp);
char						*expand_digit_variable(t_expansion *exp, char *str);
char						*expand_environment_variable(t_expansion *exp,
								char *str);
char						*add_quote_to_result(t_expansion *exp, char c);
void						process_dollar(t_expansion *exp, char *str);
void						handle_new_command(t_cmd_context *cmd_ctx,
								t_token **current_token);
void						handle_argument(t_cmd_context *cmd_ctx,
								t_token **current_token);
void						handle_pipe(t_cmd_context *cmd_ctx,
								t_token **current_token, t_type *expected);
void						handle_redirection(t_cmd_context *cmd_ctx,
								t_token **current_token, t_exec *exec);
void						expand_env_var_string(char *input, t_norm *norm,
								t_exec *exec);
void						free_tokens(t_token *token_list);
void						free_commands(t_cmd *cmd_list);
void						malloc_error(void);
int							check_quotes(char *input, t_exec *exec);
int							count_values(const char *str);
char						*remove_space(char *str);
void						handle_operator(char *input, t_helpe *helpe,
								t_exec *exec);
void						handle_s_g(char *input, t_token **token_list,
								t_helpe *helpe, t_exec *exec);

// quotes includes
bool						check_syntax_errors_before_tokenize(char *input);
int							is_dollar_followed_quote_two(char *input,
								t_norm *norm, t_exec *exec);
char						*remove_quotes(char *input, t_exec *exec,
								t_norm *norm);
char						*handle_incorrect_quotes(char *token);
int							handle_invalid_char_after_dollar(char *input,
								t_norm *norm);
int							is_dollar_followed_by_quote(char *input,
								t_norm *norm, t_exec *exec);
char						*trim_spaces(char *str);
int							is_empty_quotes_sequence(char *input, t_norm *norm,
								t_exec *exec);
char						*remove_delimiter_quotes(t_output_input *new,
								char *str);
int							check_quotes(char *input, t_exec *exec);
int							is_empty_quote_pair(char *input, t_helpe *helpe,
								t_exec *exec);
int							is_matching_quote(char *input, t_helpe *helpe,
								t_exec *exec);
int							is_whitespace_no_delimiter_or_end(char *input,
								t_helpe *helpe, t_exec *exec);
int							is_operator_no_delimiter(char *input,
								t_helpe *helpe, t_exec *exec);
int							is_operator_with_delimiter(char *input,
								t_helpe *helpe, t_exec *exec);
int							is_dollar_sign_logic(char *input, t_helpe *helpe,
								t_exec *exec);
void						finalize_and_free(t_helpe *helpe,
								t_token **token_list, t_exec *exec);
bool						validate_command_list(t_cmd *cmd_list,
								t_token *token_list, char *input);
bool						validate_input(char *input);
char						*check_me(t_exec *exec, char *res);

//////////////////////////////////////

// PROTOTYPES :

void						free_everything_data(t_exec *data);
void						initialize_everything(t_exec *data, char **envp,
								char **av, int ac);
void						handle_sig(void);
const char					*prompt(char *prompt_char);
void						env_list(t_linked **list, char **envp, char **av);
void						exec(t_exec *data, t_cmd *input);
void						execve_handle_simple(t_exec *data, t_cmd *input,
								int read_fd, int write_fd);
void						creat_node(t_linked **list, char *key, char *value,
								int flag);
void						clear_list(t_linked **list);
void						remove_list(t_linked **list, char *key);
char						*ft_getenv(t_linked *list, char *name);
int							ft_get_export(t_linked *list, char *name);
char						*ft_getexport(t_linked *list, char *name);
void						copy_environ(t_linked **list, t_linked *environ);
int							list_size(t_linked *list);
void						print_error(char *s1, char *s2, char *s3,
								int value);
long						ft_atol(char *str);
int							handle_heredoc(t_exec *data, t_cmd **input);
int							ft_atoui(char *str);
void						update_shlvl(t_linked **environ);
void						update_(t_linked **list, t_cmd *input);

// BUILTINS :

void						pwd_simple(t_exec *data, t_cmd *input);
void						env_simple(t_exec *data, t_cmd *input);
void						echo_simple(t_exec *data, t_cmd *input);
void						cd_simple(t_exec *data, t_cmd *input);
void						exit_simple(t_exec *data, t_cmd *input);
void						export_simple(t_exec *data, t_cmd *input);
void						unset_simple(t_exec *data, t_cmd *input);

// BUILTINS HARD :

void						pwd_hard(t_exec *data, t_cmd *input);
void						env_hard(t_exec *data, t_cmd *input);
void						echo_hard(t_exec *data, t_cmd *input);
void						cd_hard(t_exec *data, t_cmd *input);
void						exit_hard(t_exec *data, t_cmd *input);
void						export_hard(t_exec *data, t_cmd *input);
void						unset_hard(t_exec *data, t_cmd *input);
void						execve_handle_hard(t_exec *data, t_cmd *input,
								int read_fd, int write_fd);

// EXEC :

////////
void						update_environ(t_exec **list);
void						ft_swap(t_linked *list1, t_linked *list2);
void						sort_list(t_linked **list);
void						print_err(t_exec *data, char *str);
void						see_if_it_exist(t_exec *data, char *str);
void						handle_not(t_exec *data, char *str);
void						handle_equal(t_exec *data, char *str);
void						print_value(t_linked *list);
void						child(t_exec *data, t_cmd *input);
size_t						key_return(char *key, char *key2);
void						handle_input_output(t_exec *data, t_cmd *input,
								int *read_fd, int *write_fd);
void						initialize_pipes(t_pipe *info, int size);
void						forking_for_pipes(t_exec *data, t_cmd *input,
								t_pipe *info, int size);
void						child__(t_exec *data, t_cmd *input, t_pipe *info,
								int id);
void						close_pipes(t_pipe *info, int size);
int							ft_size(t_cmd *iterate);
void						handle_hard(t_exec *data, t_cmd *input, int read_fd,
								int write_fd);
void						ft_acces(t_exec *data, t_cmd *input);
char						**join_to_array(char *str, char **array);
int							array_size(char **array);
int							print_err_(void);
char						**case_one(char *str);
void						turn(char **envp, t_linked *list);
void						child_function(t_exec *data, t_cmd *input);
void						child_funtion_2(t_exec *data, t_cmd *input,
								char *inp);
void						ft_handle_function(char *str, int *flag);
int							check_oldpwd(t_exec **list, char *cwd);
void						handle_plus(t_exec *data, char *str);
void						handle_arg_4(t_exec *data, char *str, int *flag,
								int j);
void						handle_arg_2(char *str, int *flag, int j);
void						handle_join(t_exec *data, char *str);
void						check_w_r(int write_fd, int read_fd);
void						check_r(int read_fd);
void						check_w(int write_fd);
int							check_pwd(t_exec **list, char *cwd);
void						free_t_pipe(t_pipe *info);
void						free_envp(t_exec *data);
void						free_everything(t_exec *data, t_cmd *input);
void						handle_null(t_exec **list);
void						update_oldpwd(t_exec **list, char *cwd);
void						unlink_files(t_exec *data, t_cmd **input);
void						free_split(char **array);
void						free_everything_cmd(t_cmd **input);
void						in_ou_free(t_exec *data, t_cmd *input,
								t_pipe *info);
////////

#endif