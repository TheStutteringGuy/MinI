/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:23:09 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/12 18:23:11 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_env_simple(char *input, t_exec *exec)
{
	return (ft_strdup2(input));
}

int	check_for_char(int c)
{
	if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97) || (c <= 57 && c >= 48)
		|| c == 95)
		return (1);
	else
		return (0);
}

char	*expand(char *input, t_exec *exec)
{
	char	*expand_val;
	char	*var;

	if (input)
	{
		var = input;
		if (exec->quote == 2 || exec->quote == 0)
			expand_val = ft_getenv(exec->environ, var);
		else
			return (ft_strdup2(var));
		if (expand_val == NULL)
			return (NULL);
		return (ft_strdup2(expand_val));
	}
	return (ft_strdup2(input));
}
