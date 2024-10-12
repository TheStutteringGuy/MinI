/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/13 00:22:16 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_arg(t_exec *data, t_cmd *input)
{
	int	i;

	i = 0;
	(void)data;
	while (input->arguments[i] != NULL)
		++i;
	if (i > 1)
	{
		print_error("pwd", "too many arguments", NULL, 1);
		exit(1);
	}
}

void	pwd_hard(t_exec *data, t_cmd *input)
{
	char	cwd[PATH_MAX];

	handle_arg(data, input);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		print_error("pwd", strerror(errno), NULL, 1);
		exit(1);
	}
	printf("%s\n", cwd);
}
