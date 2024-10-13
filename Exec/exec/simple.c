/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 02:21:40 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/13 02:18:30 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exec_child(int id)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(id, &status, 0);
	if (!WIFSIGNALED(status))
		g_last_exit_status = WEXITSTATUS(status);
	else
	{
		g_last_exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			printf("\n");
	}
}

void	execve_handle_simple(t_exec *data, t_cmd *input, int read_fd,
		int write_fd)
{
	pid_t	id;
	int		i;

	i = list_size(data->environ);
	data->envp = malloc(sizeof(char *) * (i + 1));
	data->envp[i] = NULL;
	turn(data->envp, data->environ);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(read_fd, 0);
		dup2(write_fd, 1);
		child_function(data, input);
		exit(0);
	}
	else
	{
		exec_child(id);
		free_envp(data);
	}
}
