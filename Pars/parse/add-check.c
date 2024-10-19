/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add-check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:49:49 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/19 16:54:30 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_inside_quotes(char *input, int i)
{
	bool	single_quote;
	bool	double_quote;
	int		j;

	j = 0;
	double_quote = false;
	single_quote = false;
	while (j < i)
	{
		if (input[j] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (input[j] == '\"' && !single_quote)
			double_quote = !double_quote;
		j++;
	}
	return (single_quote || double_quote);
}
