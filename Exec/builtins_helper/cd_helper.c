/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:59:29 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/14 05:54:04 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static void	update_oldpwd_export(t_exec **list, char *cwd)
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
			iterate->flag = 1;
			break ;
		}
		iterate = iterate->next;
	}
}

void	update_oldpwd(t_exec **list, char *cwd)
{
	t_linked	*iterate;

	iterate = (*list)->environ;
	while (iterate)
	{
		if (ft_strlen2(iterate->key) == ft_strlen2("OLDPWD")
			&& ft_strncmp(iterate->key, "OLDPWD", ft_strlen2("OLDPWD")) == 0)
		{
			free(iterate->value);
			iterate->value = ft_substr(cwd, 0, ft_strlen(cwd));
			iterate->flag = 1;
			break ;
		}
		iterate = iterate->next;
	}
	update_oldpwd_export(list, cwd);
}

void	update_environ(t_exec **list)
{
	t_linked	*iterate;
	char		*cwd;
	char		*str;

	cwd = ft_getenv((*list)->environ, "PWD");
	str = ft_strdup2(cwd);
	if (cwd == NULL)
	{
		handle_null(list);
		return ;
	}
	update_pwd(list);
	if (check_oldpwd(list, str) == 1)
		return ;
	update_oldpwd(list, str);
	free(str);
}
