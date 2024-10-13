/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:01 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/13 16:56:19 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void add_token(t_token **head, t_token *new_token)
{
	t_token *current;

	if (!*head)
	{
		*head = new_token;
		return;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

t_type classify_token(char *token, t_helpe *helpe, t_exec *exec)
{
	if ((ft_strcmp(token, "|") == 0) && exec->quote == 0 && helpe->isoperate == 0)
		return (PIPE);
	else if ((ft_strcmp(token, "<") == 0) && exec->quote == 0 && helpe->isoperate == 0)
		return (RED_IN);
	else if ((ft_strcmp(token, ">") == 0) && exec->quote == 0 && helpe->isoperate == 0)
		return (RED_OUT);
	else if ((ft_strcmp(token, "<<") == 0) && exec->quote == 0 && helpe->isoperate == 0)
		return (HERDOC);
	else if ((ft_strcmp(token, ">>") == 0) && exec->quote == 0 && helpe->isoperate == 0)
		return (APPEND);
	else
		return (*helpe->expected);
}

void handle_token(t_token **token_list, char *token, t_helpe *helpe,
				  t_exec *exec)
{
	char *processed_token;
	t_type type;
	t_token *new_token;

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

void handle_quote(char input, t_exec *exec, t_helpe *helpe)
{
	if (input == '"')
		exec->quote = 2;
	else
		exec->quote = 1;
	if (exec->delimiter == 0)
		exec->delimiter = input;
	else if (input == exec->delimiter)
	{
		exec->delimiter = 0;
		exec->quote = 0;
	}
	if (exec->not == 1)
		helpe->token[helpe->token_len++] = input;
}

static void handle_s_g(char *input, t_token **token_list, t_helpe *helpe, t_exec *exec)
{
	if (((input[helpe->i] == '\'' && input[helpe->i + 1] == '\'') || (input[helpe->i] == '"' && input[helpe->i + 1] == '"')) && input[helpe->i + 2] == '\0')
	{
		helpe->token[helpe->token_len] = '\0';
		handle_token(token_list, helpe->token, helpe, exec);
		exec->not = 0;
		helpe->token_len = 0;
	}
	else
	{
		helpe->i++;
		exec->s_d = 1;
	}
}

void handle_operator(char *input, t_helpe *helpe, t_exec *exec)
{
	helpe->isoperate = 1;
	helpe->token[helpe->token_len++] = input[helpe->i];
}

void tokenize_input(char *input, t_token **token_list, t_exec *exec)
{
	t_helpe *helpe;

	helpe = initialize_helper(input);
	if (!helpe)
		return;
	initialize_exec(exec);
	exec->s_d = 0;
	while (input[helpe->i] != '\0')
	{
		if ((input[helpe->i] == '\'' && input[helpe->i + 1] == '\'') || (input[helpe->i] == '"' && input[helpe->i + 1] == '"'))
			handle_s_g(input, token_list, helpe, exec);
		else if ((input[helpe->i] == '\'' || input[helpe->i] == '"') && (exec->delimiter == 0 || input[helpe->i] == exec->delimiter))
			handle_quote(input[helpe->i], exec, helpe);
		else if (ft_isspace(input[helpe->i]) && exec->delimiter == 0)
			copy_token(token_list, helpe, exec);
		else if ((is_operator(input[helpe->i]) || is_multi_operator(&input[helpe->i])) && exec->delimiter == 0)
			handle_operators_logic(input, helpe, token_list, exec);
		else if ((is_operator(input[helpe->i]) || is_multi_operator(&input[helpe->i])) && exec->delimiter != 0)
			handle_operator(input, helpe, exec);
		else if (input[helpe->i] == '$' && (exec->delimiter == 0 || exec->delimiter != '\'') && exec->not == 0)
			handle_dollar_sign_logic(input, helpe, token_list, exec);
		else
			helpe->token[helpe->token_len++] = input[helpe->i];
		helpe->i++;
	}
	finalize_tokens(helpe, token_list, exec);
	free_helpe(helpe);
}
