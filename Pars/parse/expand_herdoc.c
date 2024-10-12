/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:02:15 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/12 16:24:06 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void process_quote(t_expansion *exp, char c)
{
    exp->res = add_quote_to_result(exp, c);
    exp->i++;
}

void process_other_character(t_expansion *exp, char c)
{
    exp->res = add_quote_to_result(exp, c);
    exp->i++;
}

void expand_loop(t_expansion *exp, char *str)
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

char *expand_herdoc(char *str, t_exec *exec)
{
    t_expansion exp;

    exp.len = ft_strlen(str);
    exp.i = 0;
    exp.quote_found = 0;
    exp.exec = exec;
    exp.res = (char *)malloc(1);
    if (!exp.res)
        return (NULL);
    exp.res[0] = '\0';
    expand_loop(&exp, str);
    return (exp.res);
}
