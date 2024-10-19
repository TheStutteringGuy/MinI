/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_chekers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 02:25:57 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/19 13:57:51 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_matching_quote(char *input, t_helpe *helpe, t_exec *exec)
{
	return ((input[helpe->i] == '\'' || input[helpe->i] == '"')
		&& (exec->delimiter == 0 || input[helpe->i] == exec->delimiter));
}

int	is_whitespace_no_delimiter_or_end(char *input, t_helpe *helpe, t_exec *exec)
{
	return ((ft_isspace(input[helpe->i]) && exec->delimiter == 0)
		|| input[helpe->i] == '\0');
}

int	is_operator_no_delimiter(char *input, t_helpe *helpe, t_exec *exec)
{
	return ((is_operator(input[helpe->i])
			|| is_multi_operator(&input[helpe->i])) && exec->delimiter == 0);
}

int	is_operator_with_delimiter(char *input, t_helpe *helpe, t_exec *exec)
{
	return ((is_operator(input[helpe->i])
			|| is_multi_operator(&input[helpe->i])) && exec->delimiter != 0);
}

int	is_dollar_sign_logic(char *input, t_helpe *helpe, t_exec *exec)
{
	return (input[helpe->i] == '$' && (exec->delimiter == 0
			|| exec->delimiter != '\'') && exec->not == 0);
}
