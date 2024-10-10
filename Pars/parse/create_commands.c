/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:10 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/10 18:07:31 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd *create_new_command(t_token *token)
{
    t_cmd *new_cmd;

    new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
    {
        write(2, "malloc failed\n", 14);
        exit(1);
    }
    new_cmd->command = ft_strdup(token->value);
    new_cmd->arguments = malloc(sizeof(char *) * 2);
    if (!new_cmd->arguments)
    {
        write(2, "malloc failed\n", 14);
        exit(1);
    }
    new_cmd->arguments[0] = NULL;
    new_cmd->redirection = NULL;
    new_cmd->next = NULL;
    return (new_cmd);
}

// Add an argument to the current command
void add_argument_to_command(t_cmd *current_cmd, t_token *token)
{
    int i;
    int j;
    char **new_arguments;

    i = 0;
    while (current_cmd->arguments[i])
        i++;
    new_arguments = malloc(sizeof(char *) * (i + 2));
    if (!new_arguments)
    {
        write(2, "malloc failed\n", 14);
        exit(1);
    }
    j = 0;
    while (j < i)
    {
        new_arguments[j] = current_cmd->arguments[j];
        j++;
    }
    new_arguments[i] = ft_strdup(token->value);
    new_arguments[i + 1] = NULL;
    free(current_cmd->arguments);
    current_cmd->arguments = new_arguments;
}

// Initialize redirection parameters
t_redirection_params init_redirection_params(char *filename, char *delimiter, t_redirection_flags flags)
{
    t_redirection_params params;
    params.filename = filename;
    params.delimiter = delimiter;
    params.flags = flags;
    return (params);
}

// Process filename and create output input
void process_filename(t_output_input *new, char *filename, t_exec *exec)
{
    char *processed_filename;

    processed_filename = remove_quotes(filename, exec);
    if (processed_filename == NULL)
    {
        new->ambigious = 1;
        new->filename = ft_strdup2(filename);
    }
    else
    {
        new->ambigious = 0;
        new->filename = ft_strdup2(processed_filename);
        free(processed_filename);
    }
}

void process_delimiter(t_output_input *new, char *delimiter, t_exec *exec)
{
    char *processed_delimiter;

    if (delimiter != NULL)
    {
        exec->eof = 1;
        processed_delimiter = remove_delimiter_quotes(new, delimiter);
        new->delimiter = ft_strdup2(processed_delimiter);
        free(processed_delimiter);
    }
    else
    {
        new->delimiter = NULL;
    }
}

void add_redirection(t_output_input **redirection, t_redirection_params *params, t_exec *exec)
{
    t_output_input *new;
    t_output_input *iterate;

    new = malloc(sizeof(t_output_input));
    if (!new)
        return;
    new->whichis = params->flags.value;
    process_filename(new, params->filename, exec);
    new->append = params->flags.append;
    new->heredoc = params->flags.heredoc;
    process_delimiter(new, params->delimiter, exec);
    new->next = NULL;
    if (*redirection == NULL)
    {
        *redirection = new;
        return;
    }
    iterate = *redirection;
    while (iterate->next)
        iterate = iterate->next;
    iterate->next = new;
}

t_redirection_flags initialize_redirection_flags()
{
    t_redirection_flags flags;
    flags.heredoc = 0;
    flags.append = 0;
    flags.value = 0;
    return (flags);
}

void handle_red_in(t_cmd *current_cmd, t_token *next_token, t_exec *exec)
{
    t_redirection_flags flags;
    t_redirection_params params;

    flags = initialize_redirection_flags();
    params = init_redirection_params(next_token->value, NULL, flags);
    add_redirection(&current_cmd->redirection, &params, exec);
}

void create_heredoc(t_cmd *current_cmd, t_token *next_token, t_exec *exec)
{
    t_redirection_flags flags;
    t_redirection_params params;

    flags = initialize_redirection_flags();
    flags.heredoc = 1;
    params = init_redirection_params(next_token->value, next_token->value, flags);
    add_redirection(&current_cmd->redirection, &params, exec);
}

void handle_red_out(t_cmd *current_cmd, t_token *next_token, t_exec *exec)
{
    t_redirection_flags flags;
    t_redirection_params params;

    flags = initialize_redirection_flags();
    flags.value = 1;
    params = init_redirection_params(next_token->value, NULL, flags);
    add_redirection(&current_cmd->redirection, &params, exec);
}

void handle_append(t_cmd *current_cmd, t_token *next_token, t_exec *exec)
{
    t_redirection_flags flags;
    t_redirection_params params;

    flags = initialize_redirection_flags();
    flags.append = 1;
    flags.value = 1;
    params = init_redirection_params(next_token->value, NULL, flags);
    add_redirection(&current_cmd->redirection, &params, exec);
}

// Handle redirections
void handle_redirections(t_cmd *current_cmd, t_token **current_token, t_exec *exec)
{
    t_token *token;
    t_token *next_token;

    token = *current_token;
    next_token = token->next;

    if (next_token && (next_token->type == COMMAND || next_token->type == ARGUMENT))
    {
        if (token->type == RED_IN)
            handle_red_in(current_cmd, next_token, exec);
        else if (token->type == HERDOC)
            create_heredoc(current_cmd, next_token, exec);
        else if (token->type == RED_OUT)
            handle_red_out(current_cmd, next_token, exec);
        else if (token->type == APPEND)
            handle_append(current_cmd, next_token, exec);
        *current_token = next_token;
    }
    else
        write(2, "Error: Missing or invalid token after redirection\n", 51);
}

// Helper function to process the current token
static int process_current_token(t_cmd_context *cmd_ctx, t_token **current_token, t_exec *exec, t_type *expected)
{
    if ((*current_token)->type == PIPE && *expected == COMMAND)
    {
        if (exec->eof == 1)
        {
            process_token(cmd_ctx, current_token, expected, exec);
            return (1);
        }
        ft_error((*current_token)->value);
        return (0);
    }
    process_token(cmd_ctx, current_token, expected, exec);
    return (1);
}

// Main parsing function that iterates over the token list
t_cmd *parse_tokens(t_token *token_list, t_exec *exec)
{
    t_cmd *cmd_list;
    t_cmd *current_cmd;
    t_token *current_token;
    t_type expected;
    t_cmd_context cmd_ctx;

    cmd_list = NULL;
    current_cmd = NULL;
    current_token = token_list;
    expected = COMMAND;
    cmd_ctx.cmd_list = &cmd_list;
    cmd_ctx.current_cmd = &current_cmd;
    while (current_token)
    {
        if (!process_current_token(&cmd_ctx, &current_token, exec, &expected))
            return (NULL);
        current_token = current_token->next;
    }
    return (cmd_list);
}

t_cmd *create_empty_command(void)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (cmd)
    {
        cmd->command = NULL;
        cmd->arguments = NULL;
        cmd->redirection = NULL;
        cmd->next = NULL;
    }
    else
        write(2, "Error: Memory allocation failed for new command\n", 49);
    return (cmd);
}
