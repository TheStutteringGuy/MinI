/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:12:51 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/14 05:24:20 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	check_oldpwd__(t_linked **list)
{
	t_linked	*iterate;
	int			flag;

	flag = 0;
	iterate = *list;
	while (iterate)
	{
		if (ft_strlen2(iterate->key) == ft_strlen2("OLDPWD")
			&& ft_strncmp(iterate->key, "OLDPWD", ft_strlen("OLDPWD")) == 0)
			flag = 1;
		iterate = iterate->next;
	}
	if (flag == 0)
		creat_node(list, ft_substr("OLDPWD", 0, ft_strlen2("OLDPWD")),
			ft_substr("", 0, 0), 0);
}

void	copy_environ(t_linked **list, t_linked *environ)
{
	while (environ != NULL)
	{
		creat_node(list, ft_substr(environ->key, 0, ft_strlen2(environ->key)),
			ft_substr(environ->value, 0, ft_strlen2(environ->value)), 1);
		environ = environ->next;
	}
	check_oldpwd__(list);
}
