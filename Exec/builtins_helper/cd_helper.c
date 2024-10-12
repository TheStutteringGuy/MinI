/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:59:29 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/13 00:28:29 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_oldpwd(t_exec **list, char *cwd)
{
	t_linked	*iterate;
	int			flag;

	flag = 0;
	iterate = (*list)->environ;
	while (iterate)
	{
		if (ft_strlen2(iterate->key) == ft_strlen2("OLDPWD")
			&& ft_strncmp(iterate->key, "OLDPWD", ft_strlen2("OLDPWD")) == 0)
			flag = 1;
		iterate = iterate->next;
	}
	if (flag == 1)
		return (1);
	else
	{
		remove_list(&(*list)->export, ft_substr("OLDPWD", 0,
				ft_strlen2("OLDPWD")));
		creat_node(&(*list)->environ, ft_substr("OLDPWD", 0,
				ft_strlen2("OLDPWD")), ft_substr(cwd, 0, ft_strlen2(cwd)), 1);
		creat_node(&(*list)->export, ft_substr("OLDPWD", 0,
				ft_strlen2("OLDPWD")), ft_substr(cwd, 0, ft_strlen2(cwd)), 1);
		return (0);
	}
}

static void	update_pwd_export(t_exec **list)
{
	char		cwd[PATH_MAX];
	char		*key;
	t_linked	*iterate;

	getcwd(cwd, PATH_MAX);
	key = "PWD";
	iterate = (*list)->export;
	while (iterate)
	{
		if (ft_strlen2(iterate->key) == ft_strlen2(key)
			&& ft_strncmp(iterate->key, key, ft_strlen2(key)) == 0)
		{
			free(iterate->value);
			iterate->value = ft_substr(cwd, 0, ft_strlen(cwd));
			break ;
		}
		iterate = iterate->next;
	}
}

static void	update_pwd(t_exec **list)
{
	char		cwd[PATH_MAX];
	char		*key;
	t_linked	*iterate;

	getcwd(cwd, PATH_MAX);
	key = "PWD";
	if (check_pwd(list, cwd) == 0)
		return ;
	iterate = (*list)->environ;
	while (iterate)
	{
		if (ft_strlen2(iterate->key) == ft_strlen2(key)
			&& ft_strncmp(iterate->key, key, ft_strlen2(key)) == 0)
		{
			free(iterate->value);
			iterate->value = ft_substr(cwd, 0, ft_strlen(cwd));
			break ;
		}
		iterate = iterate->next;
	}
	update_pwd_export(list);
}

static void	update_export(t_exec **list, char *cwd)
{
	t_linked	*iterate;

	iterate = (*list)->export;
	while (iterate)
	{
		if (ft_strlen2(iterate->key) == ft_strlen2("OLDPWD")
			&& ft_strncmp(iterate->key, "OLDPWD", ft_strlen2("OLDPWD")) == 0)
		{
			free(iterate->value);
			iterate->value = ft_substr(cwd, 0, ft_strlen(cwd));
			break ;
		}
		iterate = iterate->next;
	}
}

void	update_environ(t_exec **list, char *cwd)
{
	t_linked	*iterate;

	update_pwd(list);
	if (check_oldpwd(list, cwd) == 0)
		return ;
	iterate = (*list)->environ;
	while (iterate)
	{
		if (ft_strlen2(iterate->key) == ft_strlen2("OLDPWD")
			&& ft_strncmp(iterate->key, "OLDPWD", ft_strlen2("OLDPWD")) == 0)
		{
			free(iterate->value);
			iterate->value = ft_substr(cwd, 0, ft_strlen(cwd));
			break ;
		}
		iterate = iterate->next;
	}
	update_export(list, cwd);
}
