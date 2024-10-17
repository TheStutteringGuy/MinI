/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:17:41 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/17 14:30:34 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void handle_dollar_sign_logic(char *input, t_helpe *helpe,
							  t_token **token_list, t_exec *exec)
{
	update_quote(exec);
	if (input[helpe->i] == '$' && ft_isdigit(input[helpe->i + 1]))
	{
		helpe->i++;
		return ;
	}
	if (input[helpe->i] == '$' && (input[helpe->i + 1] == '\0' || ft_isspace(input[helpe->i + 1])))
	{
		helpe->token[helpe->token_len] = '$';
		helpe->token_len++;
		return;
	}
	if (input[helpe->i] == '$' && (input[helpe->i + 1] == '"' || input[helpe->i + 1] == '\'') && exec->quote == 0)
		return;
	if (input[helpe->i] == '$' && (input[helpe->i + 1] == '"' || input[helpe->i + 1] == '\'') && exec->quote == 2)
	{
		helpe->token[helpe->token_len] = '$';
		helpe->token_len++;
		return;
	}
	expand_env_var(input, helpe, token_list, exec);
	helpe->i--;
}

void initialize_exec(t_exec *exec)
{
	exec->delimiter = 0;
	exec->quote = 0;
	exec->not = 0;
	exec->s_d = 0;
	exec->is_in = 0;
}

void handle_exit_status(char *input, t_helpe *helpe, t_token **token_list,
						t_exec *exec)
{
	helpe->res = ft_itoa(g_last_exit_status);
	if (helpe->res == NULL)
		exec->expand = 1;
	helpe->i++;
	handle_expansion_result(input, helpe, token_list, exec);
}

void handle_variable_expansion(char *input, t_helpe *helpe,
							   t_token **token_list, t_exec *exec)
{
	char temp[3000];
	int j;

	j = 0;
	while (input[helpe->i] && check_for_char(input[helpe->i]))
		temp[j++] = input[(helpe->i)++];
	temp[j] = '\0';
	helpe->res = expand(temp, exec);
	if (helpe->res == NULL)
	{
		exec->expand = 1;
		helpe->res = ft_strdup2("");
	}
	handle_expansion_result(input, helpe, token_list, exec);
}
