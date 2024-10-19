/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/19 17:55:29 by thestutteri      ###   ########.fr       */
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
		j = 1;
		if (input->arguments[i][0] == '-' && input->arguments[i][1] != '\0')
		{
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
	return (i);
}

static int ft_size_a(char **array)
{
	int size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

void	echo_hard(t_exec *data, t_cmd *input)
{
	int	stop;
	int	flag;

	flag = 0;
	(void)data;
	if (input->arguments[0])
	{
		stop = handle_flag(input);
		if (stop == ft_size_a(input->arguments))
			return ;
		if (stop != 0)
			flag = 1;
		while (input->arguments[stop + 1] != NULL)
		{
			printf("%s ", input->arguments[stop]);
			++stop;
		}
		printf("%s", input->arguments[stop]);
	}
	if (flag == 0)
		printf("\n");
	g_last_exit_status = 0;
}
