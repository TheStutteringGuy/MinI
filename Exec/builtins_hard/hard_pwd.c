/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/10 22:53:16 by thestutteri      ###   ########.fr       */
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
	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
}
