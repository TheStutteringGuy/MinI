/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_and_arguments.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:24:11 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/12 19:14:05 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_pipe(t_cmd_context *cmd_ctx, t_token **current_token,
		t_type *expected)
{
	t_cmd	*new_cmd;

	if (!*cmd_ctx->current_cmd)
	{
		ft_error((*current_token)->value);
		return ;
	}
	new_cmd = create_empty_command();
	if (*cmd_ctx->current_cmd)
		(*cmd_ctx->current_cmd)->next = new_cmd;
	else
		*cmd_ctx->cmd_list = new_cmd;
	*cmd_ctx->current_cmd = new_cmd;
	*expected = COMMAND;
}

static void	handle_redirection(t_cmd_context *cmd_ctx, t_token **current_token,
		t_exec *exec)
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

void	process_redirection_or_pipe(t_cmd_context *cmd_ctx,
		t_token **current_token, t_type *expected, t_exec *exec)
{
	if ((*current_token)->type == PIPE)
		handle_pipe(cmd_ctx, current_token, expected);
	else if ((*current_token)->type == RED_IN
		|| (*current_token)->type == RED_OUT || (*current_token)->type == APPEND
		|| (*current_token)->type == HERDOC)
	{
		handle_redirection(cmd_ctx, current_token, exec);
	}
}

void	process_token(t_cmd_context *cmd_ctx, t_token **current_token,
		t_type *expected, t_exec *exec)
{
	char	*expand_val;
	char	*token_val;
	size_t	len;

	token_val = (*current_token)->value;
	len = ft_strlen(token_val);
	if ((*current_token)->type == COMMAND || (*current_token)->type == ARGUMENT)
	{
		if ((*current_token)->value == NULL)
			return ;
	}
	if ((*current_token)->type == COMMAND || (*current_token)->type == ARGUMENT)
		process_command_or_argument(cmd_ctx, current_token, expected, exec);
	else if ((*current_token)->type == PIPE || (*current_token)->type == RED_IN
		|| (*current_token)->type == RED_OUT || (*current_token)->type == APPEND
		|| (*current_token)->type == HERDOC)
		process_redirection_or_pipe(cmd_ctx, current_token, expected, exec);
}
