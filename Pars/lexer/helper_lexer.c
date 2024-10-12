/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:18:31 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/12 18:18:33 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_quote(t_exec *exec)
{
	if (exec->delimiter == 0 && exec->quote == 1)
		exec->quote = 2;
}

void	append_dollar_and_handle(t_helpe *helpe, t_token **token_list,
		t_exec *exec)
{
	helpe->token[helpe->token_len++] = '$';
	helpe->token[helpe->token_len] = '\0';
	handle_token(token_list, helpe->token, helpe, exec);
	helpe->token_len = 0;
}

void	handle_dollar_at_end(t_helpe *helpe, t_token **token_list, t_exec *exec)
{
	int	k;

	k = 0;
	while (helpe->res[k] != '\0')
		helpe->token[helpe->token_len++] = helpe->res[k++];
	append_dollar_and_handle(helpe, token_list, exec);
}

void	handle_result_input(t_helpe *helpe, t_token **token_list, t_exec *exec)
{
	int	k;

	k = 0;
	while (helpe->res[k] != '\0')
	{
		if (ft_isspace(helpe->res[k]) && exec->quote != 2)
		{
			if (helpe->token_len > 0)
			{
				helpe->token[helpe->token_len] = '\0';
				handle_token(token_list, helpe->token, helpe, exec);
				helpe->token_len = 0;
			}
			while (ft_isspace(helpe->res[k]))
				k++;
		}
		else
			helpe->token[helpe->token_len++] = helpe->res[k++];
	}
}

void	check_next_characters(char *input, t_helpe *helpe)
{
	if (input[helpe->i] == '$' && check_for_char(input[helpe->i + 1]))
		return ;
}
