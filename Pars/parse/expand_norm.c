/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:58:44 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/19 13:58:45 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_invalid_char_after_dollar(char *input, t_norm *norm)
{
	if (!check_for_char(input[norm->i]))
	{
		norm->str[norm->j++] = '$';
		norm->str[norm->j++] = input[norm->i];
		norm->i++;
		return (1);
	}
	return (0);
}
