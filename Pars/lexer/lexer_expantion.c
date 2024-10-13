/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expantion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:19:13 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/12 23:29:05 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_expansion_result(char *input, t_helpe *helpe,
		t_token **token_list, t_exec *exec)
{
	int	is_dollar_at_end;

	is_dollar_at_end = 0;
	if (input[helpe->i] == '$' && (input[helpe->i + 1] == '\0'
			|| ft_isspace(input[helpe->i + 1]) || input[helpe->i + 1] == '"'))
	{
		handle_dollar_end_case(input, helpe, token_list, exec);
		return ;
	}
	if (helpe->res && *helpe->res != '\0')
	{
		handle_non_empty_result(helpe, token_list, exec, is_dollar_at_end);
	}
	if (helpe->res && *helpe->res == '\0')
	{
		if (input[helpe->i + 1] == '\0')
		{
			helpe->token[helpe->token_len] = '\0';
			handle_token(token_list, helpe->token, helpe, exec);
			exec->not = 0;
			helpe->token_len = 0;
		}
		exec->s_d = 1;
	}
}

void	expand_env_var(char *input, t_helpe *helpe, t_token **token_list,
		t_exec *exec)
{
	exec->expand = 0;
	if (input[helpe->i] == '$')
	{
		(helpe->i)++;
		if (input[helpe->i] == '?')
		{
			handle_exit_status(input, helpe, token_list, exec);
			return ;
		}
		handle_variable_expansion(input, helpe, token_list, exec);
	}
}

t_helpe	*initialize_helper(char *input)
{
	t_helpe	*helpe;

	(void)input;
	helpe = malloc(sizeof(t_helpe));
	if (!helpe)
		return (NULL);
	helpe->i = 0;
	helpe->token_len = 0;
	helpe->isoperate = 0;
	helpe->token = malloc(3000 * sizeof(char));
	if (!helpe->token)
	{
		free(helpe);
		return (NULL);
	}
	helpe->expected = malloc(sizeof(t_type));
	if (!helpe->expected)
	{
		free(helpe->token);
		free(helpe);
		return (NULL);
	}
	*helpe->expected = COMMAND;
	return (helpe);
}

void	handle_operators_logic(char *input, t_helpe *helpe,
		t_token **token_list, t_exec *exec)
{
	if (helpe->token_len > 0)
		finalize_token(token_list, helpe, exec);
	if (is_multi_operator(&input[helpe->i]))
		add_multi_operator(helpe->token, input, &helpe->token_len, &helpe->i);
	else
		helpe->token[helpe->token_len++] = input[helpe->i];
	finalize_token(token_list, helpe, exec);
	exec->not = 1;
}

void	finalize_tokens(t_helpe *helpe, t_token **token_list, t_exec *exec)
{
	if (helpe->token_len > 0)
	{
		helpe->token[helpe->token_len] = '\0';
		handle_token(token_list, helpe->token, helpe, exec);
	}
}
