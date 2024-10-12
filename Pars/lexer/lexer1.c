/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:19:46 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/12 23:11:32 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*create_token(t_type type, char *value)
{
	t_token	*new_token;

	if (value == NULL)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	return (new_token);
}

void	free_helpe(t_helpe *helpe)
{
	free(helpe->token);
	free(helpe->expected);
	free(helpe);
	return ;
}

void	copy_token(t_token **token_list, t_helpe *helpe, t_exec *exec)
{
	if (helpe->token_len == 0 && exec->s_d == 1)
	{
		helpe->token[helpe->token_len] = '\0';
		handle_token(token_list, helpe->token, helpe, exec);
		exec->not = 0;
		helpe->token_len = 0;
		exec->s_d = 0;
	}
	else if (helpe->token_len > 0)
	{
		helpe->token[helpe->token_len] = '\0';
		handle_token(token_list, helpe->token, helpe, exec);
		exec->not = 0;
		helpe->token_len = 0;
	}
}

void	finalize_token(t_token **token_list, t_helpe *helpe, t_exec *exec)
{
	helpe->token[helpe->token_len] = '\0';
	handle_token(token_list, helpe->token, helpe, exec);
	helpe->token_len = 0;
}

void	add_multi_operator(char *token, const char *input, int *token_len,
		int *i)
{
	token[(*token_len)++] = input[(*i)++];
	token[(*token_len)++] = input[*i];
}
