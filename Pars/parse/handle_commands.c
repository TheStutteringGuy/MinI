/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:15 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/10 18:14:06 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void handle_new_command(t_cmd_context *cmd_ctx, t_token **current_token)
{
    t_cmd *new_cmd;

    if (*cmd_ctx->current_cmd && (*cmd_ctx->current_cmd)->command == NULL)
    {
        (*cmd_ctx->current_cmd)->command = ft_strdup((*current_token)->value);
        (*cmd_ctx->current_cmd)->arguments = malloc(sizeof(char *) * 2);
        (*cmd_ctx->current_cmd)->arguments[0] = NULL;
    }
    else
    {
        new_cmd = create_new_command(*current_token);
        if (!*cmd_ctx->cmd_list)
            *cmd_ctx->cmd_list = new_cmd;
        else
            (*cmd_ctx->current_cmd)->next = new_cmd;
        *cmd_ctx->current_cmd = new_cmd;
    }
}

// Function to handle an argument when expected is ARGUMENT
static void handle_argument(t_cmd_context *cmd_ctx, t_token **current_token)
{
    if (*cmd_ctx->current_cmd)
    {
        add_argument_to_command(*cmd_ctx->current_cmd, *current_token);
    }
}

// Main function to process COMMAND or ARGUMENT tokens
void process_command_or_argument(t_cmd_context *cmd_ctx, t_token **current_token, t_type *expected, t_exec *exec)
{
    if (*expected == COMMAND)
    {
        handle_new_command(cmd_ctx, current_token);
        *expected = ARGUMENT;
    }
    else if (*expected == ARGUMENT)
    {
        handle_argument(cmd_ctx, current_token);
    }
}


// Function to handle PIPE tokens
static void handle_pipe(t_cmd_context *cmd_ctx, t_token **current_token, t_type *expected)
{
    t_cmd *new_cmd;

    if (!*cmd_ctx->current_cmd)
    {
        ft_error((*current_token)->value);
        return;
    }
    new_cmd = create_empty_command();
    if (*cmd_ctx->current_cmd)
        (*cmd_ctx->current_cmd)->next = new_cmd;
    else
        *cmd_ctx->cmd_list = new_cmd;
    *cmd_ctx->current_cmd = new_cmd;
    *expected = COMMAND;
}

// Function to handle redirections
static void handle_redirection(t_cmd_context *cmd_ctx, t_token **current_token, t_exec *exec)
{
    if (*cmd_ctx->current_cmd)
        handle_redirections(*cmd_ctx->current_cmd, current_token, exec);
    else
    {
        *cmd_ctx->current_cmd = create_empty_command();
        if (!*cmd_ctx->cmd_list)
            *cmd_ctx->cmd_list = *cmd_ctx->current_cmd;
        handle_redirections(*cmd_ctx->current_cmd, current_token, exec);
    }
}

// Main function to process PIPE and REDIRECTION tokens
void process_redirection_or_pipe(t_cmd_context *cmd_ctx, t_token **current_token, t_type *expected, t_exec *exec)
{
    if ((*current_token)->type == PIPE)
        handle_pipe(cmd_ctx, current_token, expected);
    else if ((*current_token)->type == RED_IN || (*current_token)->type == RED_OUT ||
             (*current_token)->type == APPEND || (*current_token)->type == HERDOC)
    {
        handle_redirection(cmd_ctx, current_token, exec);
    }
}

void process_token(t_cmd_context *cmd_ctx, t_token **current_token, t_type *expected, t_exec *exec)
{
    char *expand_val;
    char *token_val;
    size_t len;

    token_val = (*current_token)->value;
    len = ft_strlen(token_val);
    if ((*current_token)->type == COMMAND || (*current_token)->type == ARGUMENT)
    {
        if ((*current_token)->value == NULL)
            return;
    }
    if ((*current_token)->type == COMMAND || (*current_token)->type == ARGUMENT)
        process_command_or_argument(cmd_ctx, current_token, expected, exec);
    else if ((*current_token)->type == PIPE || (*current_token)->type == RED_IN ||
             (*current_token)->type == RED_OUT || (*current_token)->type == APPEND ||
             (*current_token)->type == HERDOC)
        process_redirection_or_pipe(cmd_ctx, current_token, expected, exec);
}
