/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 01:40:51 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/05 16:21:15 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_arg_2(char *str, int *flag, int j)
{
	while (str[j] != '\0')
	{
		if (str[j] == '=')
			*flag = 1;
		j++;
	}
}

void	handle_arg_4(t_exec *data, char *str, int *flag, int j)
{
	while (str[j] != '\0')
	{
		if (str[j] == '+' && str[j + 1] == '=')
			*flag = 2;
		j++;
	}
}
