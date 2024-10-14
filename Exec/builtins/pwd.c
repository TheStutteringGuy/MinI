/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/14 02:20:57 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_arg(t_exec *data, t_cmd *input)
{
	int	i;

	i = 0;
	(void)data;
	while (input->arguments[i] != NULL)
		++i;
	if (i > 1)
	{
		print_error("pwd", "too many arguments", NULL, 1);
		g_last_exit_status = 1;
		return (-1);
	}
	return (0);
}

void	pwd_simple(t_exec *data, t_cmd *input)
{
	char	cwd[PATH_MAX];

	if (handle_arg(data, input) == -1)
		return ;
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		print_error("pwd", strerror(errno), NULL, 1);
		g_last_exit_status = 1;
		return ;
	}
	printf("%s\n", cwd);
	g_last_exit_status = 0;
}
