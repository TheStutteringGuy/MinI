/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:07:43 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/07 22:49:57 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_plus(t_exec *data, char *s)
{
	t_norminette	n;

	n.i = 0;
	while (s[n.i] != '+')
		n.i++;
	n.key = ft_substr(s, 0, n.i);
	if (ft_strncmp(n.key, "_", ft_strlen2(n.key)) == 0)
	{
		free(n.key);
		return ;
	}
	if (ft_get_export(data->export, n.key) == 1)
	{
		handle_join(data, s);
		return ;
	}
	free(n.key);
	n.j = n.i;
	n.i += 2;
	n.z = n.i;
	n.y = 0;
	while (s[n.i++])
		n.y++;
	creat_node(&data->environ, ft_substr(s, 0, n.j), ft_substr(s, n.z, n.y), 1);
	creat_node(&data->export, ft_substr(s, 0, n.j), ft_substr(s, n.z, n.y), 1);
}

void	handle_equal(t_exec *data, char *str)
{
	t_norminette	info;
	char			*key;

	info.i = 0;
	while (str[info.i] != '=')
		info.i++;
	info.j = info.i;
	info.z = info.j + 1;
	info.y = 0;
	info.i = info.z;
	while (str[info.i++] != '\0')
		info.y++;
	key = ft_substr(str, 0, info.j);
	if (ft_strncmp(key, "_", ft_strlen2(key)) == 0)
	{
		free(key);
		return ;
	}
	see_if_it_exist(data, ft_substr(str, 0, info.j));
	creat_node(&data->environ, ft_substr(str, 0, info.j), ft_substr(str, info.z,
			info.y), 1);
	creat_node(&data->export, ft_substr(str, 0, info.j), ft_substr(str, info.z,
			info.y), 1);
}

void	handle_not(t_exec *data, char *str)
{
	if (ft_strncmp(str, "_", ft_strlen2(str)) == 0)
		return ;
	if (ft_get_export(data->export, str) == 1)
		return ;
	creat_node(&data->export, ft_substr(str, 0, ft_strlen2(str)), ft_substr(str,
			0, 0), 0);
}

void	print_value(t_linked *list)
{
	while (list)
	{
		if (list->flag == 0)
			printf("declare -x %s\n", list->key);
		else
		{
			if (*list->value != '\0')
				printf("declare -x %s=\"%s\"\n", list->key, list->value);
			if (*list->value == '\0')
				printf("declare -x %s=\"%s\"\n", list->key, list->value);
		}
		list = list->next;
	}
}
