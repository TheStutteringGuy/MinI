/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/14 04:54:05 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_arg(t_cmd *input)
{
	int	i;

	i = 0;
	while (input->arguments[i] != NULL)
		++i;
	if (i > 1)
	{
		print_error("cd: too many arguments", NULL, NULL, 0);
		exit(1);
	}
}

static void	cd_home(t_exec *data, t_cmd *input)
{
	(void)input;
	if (chdir(ft_getenv(data->environ, "HOME")) != 0)
	{
		print_error("cd", "HOME is not set", NULL, 1);
		exit(1);
	}
}

static void	cd_oldpwd(t_exec **data)
{
	if (chdir(ft_getenv((*data)->environ, "OLDPWD")) != 0)
	{
		print_error("cd", "OLDPWD is not set", NULL, 1);
		exit(1);
	}
}

void	cd_hard(t_exec *data, t_cmd *input)
{
	if (!input->arguments[0])
		cd_home(data, input);
	else
	{
		handle_arg(input);
		if (ft_strlen2(input->arguments[0]) == ft_strlen2("-")
			&& ft_strncmp(input->arguments[0], "-",
				ft_strlen2(input->arguments[0])) == 0)
			cd_oldpwd(&data);
		else if (chdir(input->arguments[0]) != 0)
		{
			print_error("cd", input->arguments[0], strerror(errno), 2);
			exit(1);
		}
	}
	update_environ(&data);
}
