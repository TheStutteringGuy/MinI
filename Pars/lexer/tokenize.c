/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:01 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/15 16:25:56 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

t_type	classify_token(char *token, t_helpe *helpe, t_exec *exec)
{
	if ((ft_strcmp(token, "|") == 0) && exec->quote == 0
		&& helpe->isoperate == 0)
		return (PIPE);
	else if ((ft_strcmp(token, "<") == 0) && exec->quote == 0
		&& helpe->isoperate == 0)
		return (RED_IN);
	else if ((ft_strcmp(token, ">") == 0) && exec->quote == 0
		&& helpe->isoperate == 0)
		return (RED_OUT);
	else if ((ft_strcmp(token, "<<") == 0) && exec->quote == 0
		&& helpe->isoperate == 0)
		return (HERDOC);
	else if ((ft_strcmp(token, ">>") == 0) && exec->quote == 0
		&& helpe->isoperate == 0)
		return (APPEND);
	else
		return (*helpe->expected);
}

void	handle_token(t_token **token_list, char *token, t_helpe *helpe,
		t_exec *exec)
{
	t_type	type;
	t_token	*new_token;

	type = classify_token(token, helpe, exec);
	helpe->isoperate = 0;
	new_token = create_token(type, token);
	if (new_token)
		add_token(token_list, new_token);
	if (type == PIPE)
		*helpe->expected = COMMAND;
	else if (type == COMMAND)
		*helpe->expected = ARGUMENT;
}

void	handle_quote(char input, t_exec *exec, t_helpe *helpe)
{
	if (input == '"')
		exec->quote = 2;
	else
		exec->quote = 1;
	if (exec->delimiter == 0)
	{
		exec->delimiter = input;
		exec->is_in = 1;
	}
	else if (input == exec->delimiter)
	{
		exec->delimiter = 0;
		exec->quote = 0;
		exec->is_in = 0;
	}
	if (exec->not == 1)
		helpe->token[helpe->token_len++] = input;
}

void	tokenize_input(char *input, t_token **token_list, t_exec *exec)
{
	t_helpe	*helpe;

	helpe = initialize_helper(input);
	if (!helpe)
		return ;
	initialize_exec(exec);
	while (input[helpe->i] != '\0')
	{
		if (is_empty_quote_pair(input, helpe, exec))
			handle_s_g(input, token_list, helpe, exec);
		else if (is_matching_quote(input, helpe, exec))
			handle_quote(input[helpe->i], exec, helpe);
		else if (is_whitespace_no_delimiter(input, helpe, exec))
			copy_token(token_list, helpe, exec);
		else if (is_operator_no_delimiter(input, helpe, exec))
			handle_operators_logic(input, helpe, token_list, exec);
		else if (is_operator_with_delimiter(input, helpe, exec))
			handle_operator(input, helpe, exec);
		else if (is_dollar_sign_logic(input, helpe, exec))
			handle_dollar_sign_logic(input, helpe, token_list, exec);
		else
			helpe->token[helpe->token_len++] = input[helpe->i];
		helpe->i++;
	}
	finalize_and_free(helpe, token_list, exec);
}
