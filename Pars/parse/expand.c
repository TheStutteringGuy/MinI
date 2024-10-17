/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:23:09 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/17 05:15:51 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_env_simple(char *input, t_exec *exec)
{
	(void)exec;
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

char *expand(char *input, t_exec *exec)
{
    char *expand_val;
    char *var;
    char *result;

    if (input)
    {
        var = input;
        if (exec->quote == 2 || exec->quote == 0)
        {
            expand_val = ft_getenv(exec->environ, var);
            if (expand_val == NULL)
                return (NULL);
            result = ft_strdup2(expand_val);
        }
        else
            result = ft_strdup2(var);
        if (result == NULL)
            return (NULL);
        return result;
    }
    return (ft_strdup2(input));
}

