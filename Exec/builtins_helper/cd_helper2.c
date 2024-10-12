/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:22:48 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/13 00:31:04 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pwd(t_exec **list, char *cwd)
{
	t_linked	*iterate;
	int			flag;

	flag = 0;
	iterate = (*list)->environ;
	while (iterate)
	{
		if (ft_strlen2(iterate->key) == ft_strlen2("PWD")
			&& ft_strncmp(iterate->key, "PWD", ft_strlen2("PWD")) == 0)
			flag = 1;
		iterate = iterate->next;
	}
	if (flag == 1)
		return (1);
	else
	{
		see_if_it_exist(*list, ft_substr("PWD", 0, ft_strlen2("PWD")));
		creat_node(&(*list)->environ, ft_substr("PWD", 0, ft_strlen2("PWD")),
			ft_substr(cwd, 0, ft_strlen2(cwd)), 1);
		creat_node(&(*list)->export, ft_substr("PWD", 0, ft_strlen2("PWD")),
			ft_substr(cwd, 0, ft_strlen2(cwd)), 1);
		return (0);
	}
}
