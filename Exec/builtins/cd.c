/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/07 18:27:38 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_cd(char *str)
{
	return (ft_strlen2(str) == ft_strlen2("-") && ft_strncmp(str, "-",
			ft_strlen2(str)) == 0);
}

static int	handle_arg(t_exec *data, t_cmd *input)
{
	int	i;

	i = 0;
	(void)data;
	while (input->arguments[i] != NULL)
		++i;
	if (i > 1)
	{
		print_error("cd: too many arguments", NULL, NULL, 0);
		g_last_exit_status = 1;
		return (-1);
	}
	return (0);
}

static int	cd_home(t_exec *data, t_cmd *input)
{
	(void)input;
	if (chdir(ft_getenv(data->environ, "HOME")) != 0)
	{
		print_error("cd", "HOME is not set", NULL, 1);
		g_last_exit_status = 1;
		return (0);
	}
	return (1);
}

static int	cd_oldpwd(t_exec **data, t_cmd *input, char *cwd)
{
	(void)input;
	(void)cwd;
	if (chdir(ft_getenv((*data)->environ, "OLDPWD")) != 0)
	{
		print_error("cd", "OLDPWD is not set", NULL, 1);
		g_last_exit_status = 1;
		return (0);
	}
	return (1);
}

void	cd_simple(t_exec *data, t_cmd *input)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	if (!input->arguments[0])
	{
		if (cd_home(data, input) == 0)
			return ;
	}
	else
	{
		if (handle_arg(data, input) == -1)
			return ;
		if (check_cd(input->arguments[0]))
		{
			if (cd_oldpwd(&data, input, cwd) == 0)
				return ;
		}
		else if (chdir(input->arguments[0]) != 0)
		{
			print_error("cd", input->arguments[0], strerror(errno), 2);
			g_last_exit_status = 1;
			return ;
		}
	}
	update_environ(&data, cwd);
}
