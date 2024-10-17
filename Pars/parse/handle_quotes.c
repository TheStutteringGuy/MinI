/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:18 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/17 00:54:31 by thestutteri      ###   ########.fr       */
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
		exec->quote = 0;
		exec->is_in = 0;
	}
}

char *handle_count(t_norm *norm, t_exec *exec)
{
	if (norm->count == 0 && (exec->quote == 2 || exec->quote == 1))
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

int handle_env_var_expansion(char *input, t_exec *exec, t_norm *norm)
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

// int process_character(char *input, t_exec *exec, t_norm *norm)
// {
// 	int result;
// 	int k;

// 	if ((input[norm->i] == '\'' || input[norm->i] == '"') && (exec->delimiter == 0 || input[norm->i] == exec->delimiter) && exec->not == 0)
// 	{
// 		handle_quote(input[norm->i], exec);
// 		if (exec->is_in && (input[norm->i] == '"' || input[norm->i] == '\''))
// 		{
// 			int start = norm->i + 1;
// 			int end = start;
// 			while (input[end] && input[end] != input[start - 1])
// 				end++;

// 			if (input[end] == input[start - 1])
// 			{
// 				int has_dollar = 0;
// 				k = start;
// 				while (k < end)
// 				{
// 					if (input[k] == '$')
// 					{
// 						has_dollar = 1;
// 						break;
// 					}
// 					k++;
// 				}
// 				if (!has_dollar)
// 				{
// 					k = start;
// 					while (k < end)
// 						norm->str[norm->j++] = input[k++];
// 					norm->i = end;
// 					return (1);
// 				}
// 			}
// 		}
// 	}
// 	else if (input[norm->i] == '$' && (exec->delimiter == 0 || exec->delimiter != '\'') && exec->not == 0)
// 	{
// 		result = handle_env_var_expansion(input, exec, norm);
// 		if (result == 0)
// 			return (0);
// 		if (result == -1)
// 			return (-1);
// 	}
// 	else
// 	{
// 		norm->str[norm->j++] = input[norm->i];
// 	}
// 	return (1);
// }

int process_character(char *input, t_exec *exec, t_norm *norm)
{
	int result;

	if ((input[norm->i] == '\'' || input[norm->i] == '"') && (exec->delimiter == 0 || input[norm->i] == exec->delimiter) && exec->not == 0)
	{
		handle_quote(input[norm->i], exec);
		if ((exec->quote == 2 && input[norm->i + 1] == '"' && input[norm->i + 2] == '\0') 
		|| (exec->quote == 1 && input[norm->i + 1] == '\'' &&  input[norm->i + 2] == '\0'))
		{
			norm->i++;
			return (1);
		}
	}
	else if (input[norm->i] == '$' && (exec->delimiter == 0 || exec->delimiter != '\'') && exec->not == 0)
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

void handle_expansion_res(char *input, t_exec *exec, char *str1, t_norm *info)
{
	int is_dollar_at_end;
	int k;

	(void)exec;
	is_dollar_at_end = 0;
	if (input[info->i] == '$' && (input[info->i + 1] == '\0' || ft_isspace(input[info->i + 1]) || input[info->i + 1] == '"'))
	{
		k = 0;
		while (str1[k])
			info->str[info->j++] = str1[k++];
		info->str[info->j++] = '$';
		info->i++;
		return;
	}
	if (str1 && *str1 != '\0')
	{
		k = 0;
		while (str1[k])
			info->str[info->j++] = str1[k++];
	}
	if (str1 && *str1 == '\0')
		;
	free(str1);
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
		result = process_character(input, exec, norm);
		if (result == 0)
		{
			free(norm->str);
			return (NULL);
		}
		if (result == -1)
			break;
		norm->i++;
	}
	norm->str[norm->j] = '\0';
	norm->count = count_values(norm->str);
	return (handle_count(norm, exec));
}

// void amr_expand(char *input, t_exec *exec, t_norm *info)
// {
// 	char *str1;
// 	char temp[3000];
// 	int j;

// 	str1 = NULL;
// 	exec->expand = 0;
// 	info->i++;
// 	if (input[info->i] == '?')
// 	{
// 		str1 = ft_itoa(g_last_exit_status);
// 		handle_expansion_res(input, exec, str1, info);
// 		info->i++;
// 		return;
// 	}
// 	// else if (ft_isdigit(input[info->i]))
// 	// {
//     //     str1 = ft_strdup2(&input[ info->i + 1]);
//     //     handle_expansion_res(input, exec, str1, info);
// 	// 	info->i++;
// 	// 	free(str1);
//     //     return;
// 	// }
// 	j = 0;
// 	while (input[info->i] && check_for_char(input[info->i]))
// 		temp[j++] = input[(info->i)++];
// 	temp[j] = '\0';
// 	str1 = expand(temp, exec);
// 	if (str1 == NULL)
// 	{
// 		exec->expand = 1;
// 		str1 = ft_strdup2("");
// 	}
// 	handle_expansion_res(input, exec, str1, info);
// }

// void amr_handle_dollar(char *input, t_exec *exec, t_norm *info)
// {
// 	update_quote(exec);
// 	if (input[info->i] == '$' && (input[info->i + 1] == '\0' || ft_isspace(input[info->i + 1])))
// 	{
// 		info->str[info->j++] = '$';
// 		info->i++;
// 		return;
// 	}
// 	if (input[info->i] == '$' && input[info->i + 1] == '"' && exec->quote == 2)
// 	{
// 		info->str[info->j++] = '$';
// 		info->i++;
// 		return;
// 	}
// 	amr_expand(input, exec, info);
// 	info->i--;
// }

// char *amr_remove_quotes(char *input, t_exec *exec)
// {
// 	char *str;
// 	t_norm info;

// 	info.i = 0;
// 	info.j = 0;
// 	info.count = 0;
// 	info.str = malloc(sizeof(char) * 3000);
// 	if (!info.str)
// 		return (NULL);
// 	initialize_exec(exec);
// 	while (input[info.i])
// 	{
// 		if (((input[info.i] == '\'' && input[info.i + 1] == '\'') || (input[info.i] == '"' && input[info.i + 1] == '"')) && input[info.i + 2] == '\0' && exec->is_in == 0)
// 			return (ft_strdup2(""));
// 		else if ((input[info.i] == '\'' || input[info.i] == '"') && (exec->delimiter == 0 || input[info.i] == exec->delimiter))
// 			handle_quote(input[info.i], exec);
// 		else if (input[info.i] == '$' && (exec->delimiter == 0 || exec->quote == 2))
// 			amr_handle_dollar(input, exec, &info);
// 		else
// 			info.str[info.j++] = input[info.i];
// 		info.i++;
// 	}
// 	info.str[info.j] = '\0';
// 	info.count = count_values(info.str);
// 	str = handle_count(exec, &info);
// 	free(info.str);
// 	return (str);
// }
