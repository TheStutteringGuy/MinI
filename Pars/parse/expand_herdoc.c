/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:02:15 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/10 16:53:28 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *expand_exit_status(t_expansion *exp)
{
    char *status_str;

    status_str = ft_itoa(g_last_exit_status);
    if (!status_str)
        return (NULL);
    exp->res = ft_strjoin(exp->res, status_str);
    free(status_str);
    return (exp->res);
}

char *expand_digit_variable(t_expansion *exp, char *str)
{
    char temp[2];

    exp->i += 2;
    while (exp->i < exp->len && (ft_isdigit(str[exp->i]) || ft_isalnum(str[exp->i]) || str[exp->i] == '_'))
    {
        temp[0] = str[exp->i];
        temp[1] = '\0';
        exp->res = ft_strjoin(exp->res, temp);
        exp->i++;
    }
    return (exp->res);
}

char *expand_environment_variable(t_expansion *exp, char *str)
{
    char *env_value;
    char *var_name;
    size_t j;

    j = exp->i + 1;
    if (exp->i > 0 && (str[exp->i - 1] == '"' || str[exp->i - 1] == '\''))
        exp->quote_found = 1;
    while (j < exp->len && (ft_isalnum(str[j]) || str[j] == '_'))
        j++;
    var_name = ft_substr(str, exp->i + 1, j - exp->i - 1);
    env_value = ft_getenv(exp->exec->environ, var_name);
    free(var_name);
    if (env_value)
        exp->res = ft_strjoin(exp->res, env_value);
    else
        exp->res = ft_strjoin(exp->res, "");
    exp->i = j;
    return (exp->res);
}

char *add_quote_to_result(t_expansion *exp, char c)
{
    char temp[2];

    temp[0] = c;
    temp[1] = '\0';
    exp->res = ft_strjoin(exp->res, temp);
    return (exp->res);
}

void process_dollar(t_expansion *exp, char *str)
{
    if (str[exp->i + 1] == '?')
    {
        exp->res = expand_exit_status(exp);
        exp->i += 2;
    }
    else if (ft_isdigit(str[exp->i + 1]))
    {
        exp->res = expand_digit_variable(exp, str);
    }
    else
    {
        exp->res = expand_environment_variable(exp, str);
    }
}
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
