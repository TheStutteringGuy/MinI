/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:57:26 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/19 13:57:29 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	validate_input(char *input)
{
	if (input[0] == '\0')
	{
		free(input);
		return (false);
	}
	if (!handle_incorrect_quotes(input))
	{
		free(input);
		return (false);
	}
	return (true);
}

bool	validate_command_list(t_cmd *cmd_list, t_token *token_list, char *input)
{
	if (cmd_list == NULL)
	{
		free_tokens(token_list);
		free(input);
		return (false);
	}
	return (true);
}
