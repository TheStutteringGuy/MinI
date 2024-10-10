/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/10 22:57:03 by thestutteri      ###   ########.fr       */
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
	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
}
