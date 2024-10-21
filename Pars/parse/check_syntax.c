/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:06 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/21 22:43:09 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skip_whitespace(char *input, int i)
{
	while (input[i] && ft_isspace(input[i]))
		i++;
	return (i);
}

bool	check_pipe_syntax(char *input, int *i)
{
	int	next_char;

	if (input[*i] == '|')
	{
		if (input[*i + 1] == '|' || input[*i + 1] == '\0')
		{
			printf("Syntax error near unexpected token\n");
			g_last_exit_status = 2;
			return (false);
		}
		next_char = *i + 1;
		next_char = skip_whitespace(input, next_char);
		if (input[next_char] == '|')
		{
			printf("Syntax error near unexpected token\n");
			g_last_exit_status = 2;
			return (false);
		}
		(*i)++;
	}
	return (true);
}

bool	check_redirection_syntax(char *input, int *i)
{
	char	redirection;
	int		next_char;

	redirection = input[*i];
	next_char = *i + 1;
	if (input[next_char] == redirection)
		next_char++;
	next_char = skip_whitespace(input, next_char);
	if (input[next_char] == '\0' || input[next_char] == '|'
		|| input[next_char] == '<' || input[next_char] == '>')
	{
		printf("Syntax error near unexpected token\n");
		g_last_exit_status = 2;
		return (false);
	}
	return (true);
}

bool	check_token_syntax(char *input, int *i)
{
	*i = skip_whitespace(input, *i);
	if (input[*i] == '\0')
		return (true);
	if (!check_pipe_syntax(input, i))
		return (false);
	if (input[*i] == '\0')
		return (true);
	if (input[*i] == '<' || input[*i] == '>')
	{
		if (!check_redirection_syntax(input, i))
			return (false);
	}
	return (true);
}

bool	check_syntax_errors_before_tokenize(char *input)
{
	int	i;

	i = 0;
	i = skip_whitespace(input, i);
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
		if (input[i] != '\0')
			i++;
	}
	return (true);
}
