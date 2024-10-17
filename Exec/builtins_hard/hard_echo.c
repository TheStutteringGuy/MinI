/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/17 10:09:59 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_flag(t_cmd *input)
{
	int	i;
	int	j;

	i = 0;
	while (input->arguments[i] != NULL)
	{
		j = 0;
		if (input->arguments[i][j] == '-' && input->arguments[i][j + 1] != '\0')
		{
			j++;
			while (input->arguments[i][j] != '\0')
			{
				if (input->arguments[i][j] == 'n')
					j++;
				else
					return (i);
			}
		}
		else
			return (i);
		i++;
	}
	return (0);
}

void	echo_hard(t_exec *data, t_cmd *input)
{
	int	stop;
	int	flag;

	(void)data;
	flag = 0;
	if (input->arguments[0])
	{
		stop = handle_flag(input);
		if (stop != 0)
			flag = 1;
		while (input->arguments[stop] != NULL)
		{
			printf("%s ", input->arguments[stop]);
			++stop;
		}
	}
	if (flag == 0)
		printf("\n");
}
