/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:55:53 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/13 23:20:25 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_special_case(int *i)
{
	(*i)++;
	return (ft_itoa(g_last_exit_status));
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

char	*expand_and_check(char *res, char *input, int *i, t_exec *exec)
{
	if (input[*i] == '$' && (input[*i + 1] == '\0' || ft_isspace(input[*i
					+ 1])))
	{
		exec->quote = 2;
		return (ft_strjoin2(res, "$"));
	}
	return (res);
}

char	*handle_empty_or_invalid_var(int *i, char *input)
{
	if (input[*i] == '\0' || !check_for_char(input[*i]))
		return (ft_strdup2("$"));
	return (NULL);
}

char	*expand_env_var_string(char *input, int *i, t_exec *exec)
{
	char	*res;
	char	*var_name;

	(*i)++;
	if (input[*i] == '?')
		return (handle_special_case(i));
	res = handle_empty_or_invalid_var(i, input);
	if (res != NULL)
		return (res);
	var_name = get_env_var_name(input, i);
	res = expand(var_name, exec);
	free(var_name);
	if (res == NULL)
		res = "";
	return (expand_and_check(res, input, i, exec));
}
