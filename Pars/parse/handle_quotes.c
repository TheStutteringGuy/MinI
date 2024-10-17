/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:18 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/17 05:19:10 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void handle_quote(char input, t_exec *exec)
{
	if (input == '"')
		exec->quote = 2;
	else
		exec->quote = 1;
	if (exec->delimiter == 0)
	{
		exec->delimiter = input;
		exec->is_in = 1;
	}
	else if (input == exec->delimiter)
	{
		exec->delimiter = 0;
		exec->is_in = 0;
		exec->quote = 0;
	}
}

char *handle_count(t_norm *norm, t_exec *exec)
{
	if (norm->count == 0 && exec->s_d == 1)
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
	free(norm->str);
	return (norm->str1);
}

void handle_env_var_expansion(char *input, t_exec *exec, t_norm *norm)
{
	expand_env_var_string(input, norm, exec);
	norm->i--;
}

void process_character(char *input, t_exec *exec, t_norm *norm)
{
	if ((input[norm->i] == '\'' || input[norm->i] == '"') && (exec->delimiter == 0 || input[norm->i] == exec->delimiter))
	{
		handle_quote(input[norm->i], exec);
		if ((exec->quote == 2 && input[norm->i + 1] == '"' && input[norm->i + 2] == '\0') 
		|| (exec->quote == 1 && input[norm->i + 1] == '\'' &&  input[norm->i + 2] == '\0'))
		{
			norm->i++;
			return ;
		}
	}
	else if (input[norm->i] == '$' && input[norm->i + 1] == '\0')
	{
		norm->str[norm->j++] = input[norm->i];
		return ;
	}
	else if (input[norm->i] == '$' && (input[norm->i + 1] == '"' || input[norm->i + 1] == '\'') && exec->quote == 2)
	{
		norm->str[norm->j++] = input[norm->i];
		return ;
	}
	else if (input[norm->i] == '$' && (input[norm->i + 1] == '"' || input[norm->i + 1] == '\'') && exec->quote == 0)
	{
		norm->i++;
		return ;
	}
	else if (input[norm->i] == '$' && (exec->delimiter == 0 || exec->delimiter != '\''))
		handle_env_var_expansion(input, exec, norm);
	else
		norm->str[norm->j++] = input[norm->i];
}


char *remove_quotes(char *input, t_exec *exec, t_norm *norm)
{
	int result;

	norm->i = 0;
	norm->j = 0;
	norm->str = malloc(3000 * sizeof(char));
	if (!norm->str)
		return (NULL);
	initialize_exec(exec);
	while (input[norm->i] != '\0')
	{
		process_character(input, exec, norm);
		norm->i++;
	}
	norm->str[norm->j] = '\0';
	// norm->count = count_values(norm->str);
	// return (handle_count(norm, exec));
	return (norm->str);
}
