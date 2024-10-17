/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:55:53 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/17 09:14:48 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_special_case(t_norm *norm)
{
	char *str;
	int i;

	str = ft_itoa(g_last_exit_status);
	i = 0;
	while (str[i])
		norm->str[norm->j++] = str[i++];
	free(str);
}

char	*get_env_var_name(char *input, int *i)
{
	char	temp[3000];
	int		j;

	j = 0;
	while (input[*i] && check_for_char(input[*i]))
		temp[j++] = input[(*i)++];
	temp[j] = '\0';
	return (ft_strdup2(temp));
}

void expand_and_check(char *res, char *input, t_exec *exec, t_norm *norm)
{
	int dollar_in_end;
	int	k;

	dollar_in_end = 0;
	if (input[norm->i] == '$' && (input[norm->i + 1] == '\0' || ft_isspace(input[norm->i + 1]) || input[norm->i + 1] == '"'))
		dollar_in_end = 1;
	if (res && *res != 0)
	{
		k = 0;
		while (res[k])
			norm->str[norm->j++] = res[k++];
		if (dollar_in_end == 1)
		{
			norm->str[norm->j++] = '$';
			norm->i++;
		}
		free(res);
		return ;
	}
	if (res && *res == 0)
	{
		if (exec->quote == 2)
			exec->s_d = 1;
	}
}

char	*handle_empty_or_invalid_var(int *i, char *input)
{
	if (input[*i] == '\0' || !check_for_char(input[*i]))
		return (ft_strdup2("$"));
	return (NULL);
}

void 	expand_env_var_string(char *input, t_norm *norm, t_exec *exec)
{
	char	*res;
	char	*var_name;

	norm->i++;
	if (input[norm->i] == '?')
	{
		handle_special_case(norm);
		norm->i++;
		return ;
	}
	var_name = get_env_var_name(input, &norm->i);
	res = expand(var_name, exec);
	free(var_name);
	if (res == NULL)
		res = "";
	if (exec->quote == 2)
		exec->expand = 0;
	else
		exec->expand = 1;
	expand_and_check(res, input, exec, norm);
}
