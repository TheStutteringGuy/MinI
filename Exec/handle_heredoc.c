/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:30:08 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/22 01:21:30 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static volatile sig_atomic_t signal_received = 0;

// static void sig_handle(int sig)
// {
//     signal_received = 1;
// }

static void	make_name_2(t_output_input **list)
{
	t_output_input	*iterate;
	static int		i;
	char			*join;
	char			*itoa_;

	iterate = *list;
	while (iterate)
	{
		if (iterate->heredoc == true)
		{
			itoa_ = ft_itoa(i);
			join = ft_strjoin2("/tmp/heredoc", itoa_);
			free(itoa_);
			iterate->heredoc_file = ft_substr(join, 0, ft_strlen2(join));
			free(join);
			i++;
		}
		iterate = iterate->next;
	}
}

static void	make_names(t_cmd **input)
{
	t_cmd	*curr;

	curr = *input;
	while (curr)
	{
		make_name_2(&curr->redirection);
		curr = curr->next;
	}
}

static int	size(t_cmd *iterate)
{
	int				size;
	t_output_input	*curr;

	size = 0;
	while (iterate)
	{
		curr = iterate->redirection;
		while (curr)
		{
			if (curr->whichis == false)
			{
				if (curr->heredoc == true)
					size++;
			}
			curr = curr->next;
		}
		iterate = iterate->next;
	}
	return (size);
}

void	free_herd(t_exec *data, t_cmd *input)
{
	print_error("maximum here-document count exceeded", NULL, NULL, 0);
	free_everything(data, input);
}

int	handle_heredoc(t_exec *data, t_cmd **input)
{
	pid_t	id;
	int		status;

	if (size(*input) > 16)
	{
		free_herd(data, *input);
		exit(2);
	}
	if (size(*input) == 0)
		return (0);
	make_names(input);
	id = fork();
	if (id == 0)
		child(data, *input);
	signal(SIGINT, SIG_IGN);
	waitpid(id, &status, 0);
	if (!WIFSIGNALED(status))
		g_last_exit_status = WEXITSTATUS(status);
	else
	{
		g_last_exit_status = 128 + WTERMSIG(status);
		unlink_files(data, input);
		return (-1);
	}
	return (0);
}
