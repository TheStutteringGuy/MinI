/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:06 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/21 23:19:46 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	skip_quotes(char *input, int *i)
{
	char	quote;

	if (input[*i] == '\'' || input[*i] == '"')
	{
		quote = input[*i];
		(*i)++;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (input[*i] == quote)
			(*i)++;
		return (true);
	}
	return (false);
}

bool	check_pipe_syntax(char *input, int *i)
{
	int	next_char;

	if (input[*i] == '|')
	{
		(*i)++;
		next_char = skip_whitespace(input, *i);
		if (input[next_char] == '|' || input[next_char] == '\0')
		{
			printf("Syntax error near unexpected token\n");
			g_last_exit_status = 2;
			return (false);
		}
		*i = next_char;
	}
	return (true);
}

bool	check_redirection_syntax(char *input, int *i)
{
	char	redirection;
	int		next_char;

	redirection = input[*i];
	(*i)++;
	if (input[*i] == redirection)
		(*i)++;
	next_char = skip_whitespace(input, *i);
	if (input[next_char] == '\0' || input[next_char] == '|'
		|| input[next_char] == '<' || input[next_char] == '>')
	{
		printf("Syntax error near unexpected token\n");
		g_last_exit_status = 2;
		return (false);
	}
	*i = next_char;
	return (true);
}

bool	check_token_syntax(char *input, int *i)
{
	*i = skip_whitespace(input, *i);
	while (input[*i] != '\0')
	{
		if (skip_quotes(input, i))
			continue ;
		if (input[*i] == '|')
		{
			if (!check_pipe_syntax(input, i))
				return (false);
		}
		else if (input[*i] == '<' || input[*i] == '>')
		{
			if (!check_redirection_syntax(input, i))
				return (false);
		}
		else
			(*i)++;
	}
	return (true);
}

bool	check_syntax_errors_before_tokenize(char *input)
{
	int	i;

	i = skip_whitespace(input, 0);
	if (input[i] == '|')
	{
		printf("Syntax error near unexpected token\n");
		g_last_exit_status = 2;
		return (false);
	}
	while (input[i] != '\0')
	{
		if (!check_token_syntax(input, &i))
			return (false);
	}
	return (true);
}
