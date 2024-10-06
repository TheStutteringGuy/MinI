/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:53:52 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/06 20:04:59 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check__(char *command, char *str)
{
	return (ft_strlen2(command) == ft_strlen2(str) && ft_strncmp(command, str,
			ft_strlen2(str)) == 0);
}

void	handle_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
	int	saved_fd;

	saved_fd = dup(STDOUT_FILENO);
	if (write_fd != 1)
		dup2(write_fd, STDOUT_FILENO);
	if (check__(input->command, "pwd"))
		pwd_simple(data, input, read_fd, write_fd);
	else if (check__(input->command, "env"))
		env_simple(data, input, read_fd, write_fd);
	else if (check__(input->command, "echo"))
		echo_simple(data, input, read_fd, write_fd);
	else if (check__(input->command, "cd"))
		cd_simple(data, input, read_fd, write_fd);
	else if (check__(input->command, "exit"))
		exit_simple(data, input, read_fd, write_fd);
	else if (check__(input->command, "export"))
		export_simple(data, input, read_fd, write_fd);
	else if (check__(input->command, "unset"))
		unset_simple(data, input, read_fd, write_fd);
	else
		execve_handle_simple(data, input, read_fd, write_fd);
	if (write_fd != 1)
		dup2(saved_fd, STDOUT_FILENO);
	close(saved_fd);
}

void	handle_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
	int		saved_fd;
	size_t	len;

	if (!input->command)
		return ;
	if (check__(input->command, "pwd"))
		pwd_hard(data, input, read_fd, write_fd);
	else if (check__(input->command, "env"))
		env_hard(data, input, read_fd, write_fd);
	else if (check__(input->command, "echo"))
		echo_hard(data, input, read_fd, write_fd);
	else if (check__(input->command, "cd"))
		cd_hard(data, input, read_fd, write_fd);
	else if (check__(input->command, "exit"))
		exit_hard(data, input, read_fd, write_fd);
	else if (check__(input->command, "export"))
		export_hard(data, input, read_fd, write_fd);
	else if (check__(input->command, "unset"))
		unset_hard(data, input, read_fd, write_fd);
	else
		execve_handle_hard(data, input, read_fd, write_fd);
}

void	exec_(t_exec *data, t_cmd *input)
{
	int		status;
	t_pipe	info;
	int		i;

	signal(SIGINT, SIG_IGN);
	info.size = ft_size(input);
	info.pid_list = malloc(sizeof(pid_t) * info.size);
	initialize_pipes(&info, info.size - 1);
	forking_for_pipes(data, input, &info, info.size);
	close_pipes(&info, info.size - 1);
	i = 0;
	while (i < info.size)
	{
		waitpid(info.pid_list[i], &status, 0);
		if (!WIFSIGNALED(status))
			g_last_exit_status = WEXITSTATUS(status);
		else
		{
			g_last_exit_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGINT)
				printf("\n");
		}
		i++;
	}
}

void	exec(t_exec *data, t_cmd *input)
{
	pid_t	id;
	int		write_fd;
	int		read_fd;

	if (handle_heredoc(data, &input) == -1)
	{
		printf("\n");
		return ;
	}
	handle_sig();
	if (!input->next)
	{
		read_fd = 0;
		write_fd = 1;
		handle_input_output(data, input, &read_fd, &write_fd);
		if (read_fd == -1)
			return ;
		if (write_fd == -1)
			return ;
		update_(&data->environ, input);
		if (input->command)
			handle_simple(data, input, read_fd, write_fd);
	}
	else
		exec_(data, input);
}
