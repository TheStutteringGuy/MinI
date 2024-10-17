/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_simple_help2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 23:31:01 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/17 01:10:54 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void isdir_free(t_exec *data, t_cmd *input)
{
	print_error(input->command, "Is a directory", NULL, 1);
	free_everything(data, input);
	free_envp(data);
	exit(126);	
}

void	ft_acces(t_exec *data, t_cmd *input)
{
	struct stat	info;

	if (stat(input->command, &info) == 0)
	{
		if (S_ISDIR(info.st_mode) != 0)
			isdir_free(data, input);
	}
	if (access(input->command, F_OK | X_OK) == 0)
	{
		data->arg = join_to_array(input->command, input->arguments);
		execve(input->command, data->arg, data->envp);
	}
	else
	{
		print_error(input->command, strerror(errno), NULL, 1);
		free_envp(data);
		free_everything(data, input);
		if (errno == ENOENT)
			exit(127);
		if (errno == EACCES || errno == ENOTDIR)
			exit(126);
	}
	exit(0);
}
