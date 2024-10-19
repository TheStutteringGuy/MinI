/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:10 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/19 14:00:52 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*create_new_command(t_token *token)
{
	t_cmd	*new_cmd;

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

void	add_argument_to_command(t_cmd *current_cmd, t_token *token)
{
	int		i;
	int		j;
	char	**new_arguments;

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

int	process_current_token(t_cmd_context *cmd_ctx, t_token **current_token,
		t_exec *exec, t_type *expected)
{
	if ((*current_token)->type == PIPE && *expected == COMMAND)
	{
		if (exec->eof == 1)
		{
			process_token(cmd_ctx, current_token, expected, exec);
			return (1);
		}
		return (0);
	}
	process_token(cmd_ctx, current_token, expected, exec);
	return (1);
}

t_cmd	*parse_tokens(t_token *token_list, t_exec *exec)
{
	t_cmd			*cmd_list;
	t_cmd			*current_cmd;
	t_token			*current_token;
	t_type			expected;
	t_cmd_context	cmd_ctx;

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

t_cmd	*create_empty_command(void)
{
	t_cmd	*cmd;

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
