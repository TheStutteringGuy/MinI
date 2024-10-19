/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:22:48 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/19 16:44:25 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_null(t_exec **list)
{
	t_linked	*iterate;

	remove_list(&(*list)->environ, "OLDPWD");
	if (ft_get_export((*list)->export, "OLDPWD") == 0)
		return ;
	iterate = (*list)->export;
	while (iterate)
	{
		if (ft_strlen2(iterate->key) == ft_strlen2("OLDPWD")
			&& ft_strncmp(iterate->key, "OLDPWD", ft_strlen2("OLDPWD")) == 0)
		{
			free(iterate->value);
			iterate->value = ft_strdup2("");
			iterate->flag = 0;
			break ;
		}
		iterate = iterate->next;
	}
}

int	check_oldpwd(t_exec **list, char *cwd)
{
	t_linked	*iterate;
	int			flag;

	flag = 0;
	iterate = (*list)->export;
	while (iterate)
	{
		if (ft_strlen2(iterate->key) == ft_strlen2("OLDPWD")
			&& ft_strncmp(iterate->key, "OLDPWD", ft_strlen2("OLDPWD")) == 0)
			flag = 1;
		iterate = iterate->next;
	}
	if (flag == 0)
		return (1);
	else
	{
		if (ft_get_export((*list)->environ, "OLDPWD") == 0)
			creat_node(&(*list)->environ, ft_substr("OLDPWD", 0,
					ft_strlen2("OLDPWD")), ft_strdup2(""), 1);
		update_oldpwd(list, cwd);
		return (0);
	}
}

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
