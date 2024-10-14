/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:06:15 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/14 07:21:55 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update(t_linked **list, char *str)
{
	char	*key;

	key = "_";
	remove_list(list, key);
	creat_node(list, ft_substr(key, 0, ft_strlen2(key)), ft_substr(str, 0,
			ft_strlen2(str)), 1);
}

void	update_(t_linked **list, t_cmd *input)
{
	char	*new_value;
	int		i;

	i = 0;
	if (!input->command && !input->arguments)
	{
		update(list, "");
		return ;
	}
	if (!input->arguments[0])
		new_value = input->command;
	else
	{
		while (input->arguments[i + 1] != NULL)
			i++;
		new_value = input->arguments[i];
	}
	update(list, new_value);
}
