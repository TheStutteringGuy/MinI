/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:18 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/13 19:59:21 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_quote(char input, t_exec *exec)
{
	if (input == '"')
		exec->quote = 2;
	else
		exec->quote = 1;
	if (exec->delimiter == 0)
		exec->delimiter = input;
	else if (input == exec->delimiter)
	{
		exec->delimiter = 0;
		exec->quote = 0;
	}
}

char	*handle_count(t_norm *norm, t_exec *exec)
{
	if (norm->count == 0 && exec->quote == 2)
		return (ft_strdup2(""));
	else if (norm->count == 0)
		return (NULL);
	if (norm->count >= 2)
	{
		if (exec->quote == 2)
			return (norm->str);
		else
			return (NULL);
	}
	norm->str1 = remove_space(norm->str);
	return (norm->str1);
}

int	handle_env_var_expansion(char *input, t_exec *exec, t_norm *norm)
{
	norm->expanded = expand_env_var_string(input, &norm->i, exec);
	if (!norm->expanded)
	{
		free(norm->str);
		return (0);
	}
	while (*(norm->expanded))
	{
		norm->str[norm->j++] = *(norm->expanded)++;
	}
	if (input[norm->i] == '$' && input[norm->i + 1] == '\0')
		return (-1);
	norm->i--;
	return (1);
}

int	process_character(char *input, t_exec *exec, t_norm *norm)
{
	int	result;

	if ((input[norm->i] == '\'' || input[norm->i] == '"')
		&& (exec->delimiter == 0 || input[norm->i] == exec->delimiter)
		&& exec->not == 0)
	{
		handle_quote(input[norm->i], exec);
	}
	else if (input[norm->i] == '$' && (exec->delimiter == 0
			|| exec->delimiter != '\'') && exec->not == 0)
	{
		result = handle_env_var_expansion(input, exec, norm);
		if (result == 0)
			return (0);
		if (result == -1)
			return (-1);
	}
	else
	{
		norm->str[norm->j++] = input[norm->i];
	}
	return (1);
}

char	*remove_quotes(char *input, t_exec *exec, t_norm *norm)
{
	int	result;

	norm->i = 0;
	norm->j = 0;
	norm->str = malloc(3000 * sizeof(char));
	if (!norm->str)
		return (NULL);
	initialize_exec(exec);
	while (input[norm->i] != '\0')
	{
		result = process_character(input, exec, norm);
		if (result == 0)
		{
			free(norm->str);
			return (NULL);
		}
		if (result == -1)
			break ;
		norm->i++;
	}
	norm->str[norm->j] = '\0';
	norm->count = count_values(norm->str);
	return (handle_count(norm, exec));
}
