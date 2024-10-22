/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:59:40 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/21 23:47:10 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_quotes(char *input, t_exec *exec)
{
	(void)input;
	
	if (exec->quote == 1)
		return (1);
	else if (exec->quote == 2)
		return (2);
	else
		return (0);
}

int	count_values(const char *str)
{
	int	count;
	int	in_value;

	count = 0;
	in_value = 0;
	while (*str)
	{
		if (!ft_isspace(*str))
		{
			if (!in_value)
			{
				count++;
				in_value = 1;
			}
		}
		else
		{
			in_value = 0;
		}
		str++;
	}
	return (count);
}

char	*remove_space(char *str)
{
	int		i;
	int		j;
	size_t	length;
	char	*res;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	length = ft_strlen2(str);
	res = malloc(length + 1);
	if (res == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

char	*handle_quote_error(void)
{
	write(2, "Syntax error: unclosed quotes\n", 31);
	g_last_exit_status = 2;
	return (NULL);
}

char	*handle_incorrect_quotes(char *token)
{
	int		i;
	char	quots;

	i = 0;
	quots = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '"')
		{
			if (quots == 0)
				quots = token[i];
			else if (token[i] == quots)
				quots = 0;
			i++;
		}
		else
			i++;
	}
	if (quots != 0)
		return (handle_quote_error());
	else
		return (token);
}
