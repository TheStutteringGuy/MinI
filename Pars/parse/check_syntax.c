/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:06 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/17 19:08:20 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int skip_whitespace(char *input, int i)
{
	while (input[i] && ft_isspace(input[i]))
		i++;
	return (i);
}

bool check_pipe_syntax(char *input, int *i)
{
	int next_char;

	if (input[*i] == '|')
	{
		if (input[*i + 1] == '|' || input[*i + 1] == '\0')
		{
			printf("Syntax error near unexpected token `|'\n");
			return (false);
		}
		next_char = *i + 1;
		next_char = skip_whitespace(input, next_char);
		if (input[next_char] == '|')
		{
			printf("Syntax error near unexpected token `|'\n");
			return (false);
		}
		(*i)++;
	}
	return (true);
}

bool check_redirection_syntax(char *input, int *i)
{
	char redirection;
	int next_char;

	redirection = input[*i];
	next_char = *i + 1;
	if (input[next_char] == redirection)
		next_char++;
	next_char = skip_whitespace(input, next_char);
	if (input[next_char] == '\0' || input[next_char] == '|' ||
		input[next_char] == '<' || input[next_char] == '>')
	{
		printf("Syntax error near unexpected token `%c'\n", redirection);
		return (false);
	}
	return (true);
}

bool check_syntax_errors_before_tokenize(char *input)
{
	int i;

	i = 0;
	i = skip_whitespace(input, i);
	if (input[i] == '|')
	{
		printf("Syntax error near unexpected token `|'\n");
		return (false);
	}
	while (input[i] != '\0')
	{
		i = skip_whitespace(input, i);
		if (!check_pipe_syntax(input, &i))
			return (false);
		if (input[i] == '<' || input[i] == '>')
		{
			if (!check_redirection_syntax(input, &i))
				return (false);
		}
		i++;
	}
	return (true);
}

char *trim_spaces(char *str)
{
	while (ft_isspace((unsigned char)*str))
		str++;
	return (ft_strdup(str));
}
