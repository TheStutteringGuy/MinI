/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/07 22:22:18 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset_hard(t_exec *data, t_cmd *input)
{
	int	i;

	i = -1;
	if (input->arguments[0])
	{
		while (input->arguments[++i] != NULL)
		{
			if (ft_strncmp(input->arguments[i], "_",
					ft_strlen2(input->arguments[i])) == 0)
				continue ;
			remove_list(&data->environ, input->arguments[i]);
			remove_list(&data->export, input->arguments[i]);
		}
	}
}
