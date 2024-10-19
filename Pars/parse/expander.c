/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:55:53 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/20 00:06:34 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env_var_name(char *input, int *i)
{
	char	temp[4194304];
	int		j;

	j = 0;
	while (input[*i] && check_for_char(input[*i]))
		temp[j++] = input[(*i)++];
	temp[j] = '\0';
	return (ft_strdup2(temp));
}

int	check_dollar_in_end(char *input, t_norm *norm)
{
	if (input[norm->i] == '$' && (input[norm->i + 1] == '\0'
			|| ft_isspace(input[norm->i + 1]) || input[norm->i + 1] == '"'))
		return (1);
	return (0);
}

void	expand_and_check(char *res, char *input, t_exec *exec, t_norm *norm)
{
	int	dollar_in_end;
	int	k;

	dollar_in_end = check_dollar_in_end(input, norm);
	if (res && *res != 0)
	{
		k = 0;
		while (res[k])
			norm->str[norm->j++] = res[k++];
		if (dollar_in_end == 1)
		{
			exec->expand = 0;
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
		free(res);
	}
}

char	*handle_empty_or_invalid_var(int *i, char *input)
{
	if (input[*i] == '\0' || !check_for_char(input[*i]))
		return (ft_strdup2("$"));
	return (NULL);
}

void	expand_env_var_string(char *input, t_norm *norm, t_exec *exec)
{
	char	*res;
	char	*var_name;
	char	*res1;

	norm->i++;
	if (input[norm->i] == '?')
	{
		handle_special_case(norm);
		return ;
	}
	if (handle_invalid_char_after_dollar(input, norm))
		return ;
	var_name = get_env_var_name(input, &norm->i);
	res = expand(var_name, exec);
	free(var_name);
	if (res == NULL)
		res = ft_strdup2("");
	if (exec->quote == 2)
	{
		if (exec->expand != 1)
			exec->expand = 0;
	}
	res1 = check_me(exec, res);
	free(res);
	expand_and_check(res1, input, exec, norm);
}
