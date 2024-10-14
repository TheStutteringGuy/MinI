/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:53:59 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/13 20:05:47 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_s_g(char *input, t_token **token_list, t_helpe *helpe,
		t_exec *exec)
{
	if (((input[helpe->i] == '\'' && input[helpe->i + 1] == '\'')
			|| (input[helpe->i] == '"' && input[helpe->i + 1] == '"'))
		&& input[helpe->i + 2] == '\0')
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

void	handle_operator(char *input, t_helpe *helpe, t_exec *exec)
{
	(void)exec;
	helpe->isoperate = 1;
	helpe->token[helpe->token_len++] = input[helpe->i];
}
