/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:02:15 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/17 01:49:45 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process_quote(t_expansion *exp, char c)
{
	exp->res = add_quote_to_result(exp, c);
	exp->i++;
}

void	process_other_character(t_expansion *exp, char c)
{
	exp->res = add_quote_to_result(exp, c);
	exp->i++;
}

void	expand_loop(t_expansion *exp, char *str)
{
	while (exp->i < exp->len)
	{
		if (str[exp->i] == '$')
		{
			process_dollar(exp, str);
		}
		else if (str[exp->i] == '\"' || str[exp->i] == '\'')
		{
			process_quote(exp, str[exp->i]);
		}
		else
		{
			process_other_character(exp, str[exp->i]);
		}
	}
}

char	*expand_herdoc(char *str, t_exec *exec)
{
	t_expansion	exp;

	exp.len = ft_strlen(str);
	exp.i = 0;
	exp.quote_found = 0;
	exp.exec = exec;
	exp.res = NULL;
	expand_loop(&exp, str);
	printf("---->   %s\n", exp.res);
	return (exp.res);
}
