/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 02:25:46 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/15 04:52:23 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_empty_quote_pair(char *input, t_helpe *helpe, t_exec *exec)
{
	return (((input[helpe->i] == '\'' && input[helpe->i + 1] == '\'')
			|| (input[helpe->i] == '"' && input[helpe->i + 1] == '"'))
		&& exec->is_in == 0 && exec->not == 0);
}

void	finalize_and_free(t_helpe *helpe, t_token **token_list, t_exec *exec)
{
	finalize_tokens(helpe, token_list, exec);
	if (helpe)
	{
		free(helpe->token);
		free(helpe->expected);
		free(helpe);
	}
}
