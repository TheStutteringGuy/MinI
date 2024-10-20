/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:31:32 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/20 02:45:32 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_join(t_exec *data, char *str)
{
	t_norminette	var;
	char			*value;
	char			*value_saved;
	char			*str1;

	var.i = 0;
	while (str[var.i] != '+')
		var.i++;
	var.j = var.i;
	var.i += 2;
	var.z = var.i;
	var.y = 0;
	while (str[var.i++])
		var.y++;
	var.key = ft_substr(str, 0, var.j);
	value = ft_getexport(data->export, var.key);
	value_saved = ft_strdup2(value);
	str1 = ft_substr(str, var.z, var.y);
	see_if_it_exist(data, var.key);
	creat_node(&data->environ, ft_substr(str, 0, var.j),
		ft_strjoin2(value_saved, str1), 1);
	creat_node(&data->export, ft_substr(str, 0, var.j), ft_strjoin2(value_saved,
			str1), 1);
	free(str1);
	free(value_saved);
}
