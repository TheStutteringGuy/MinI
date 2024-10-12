/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:15 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/12 20:36:23 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_new_command(t_cmd_context *cmd_ctx, t_token **current_token)
{
	t_cmd	*new_cmd;

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

void	handle_argument(t_cmd_context *cmd_ctx, t_token **current_token)
{
	if (*cmd_ctx->current_cmd)
	{
		add_argument_to_command(*cmd_ctx->current_cmd, *current_token);
	}
}

void	process_command_or_argument(t_cmd_context *cmd_ctx,
		t_token **current_token, t_type *expected, t_exec *exec)
{
	(void)exec;
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
