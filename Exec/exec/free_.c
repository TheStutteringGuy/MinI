/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 02:03:04 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/15 02:23:56 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_everything(t_exec *data, t_cmd *input)
{
	free_everything_cmd(&input);
	clear_list(&data->environ);
	free(data->environ);
	clear_list(&data->export);
	free(data->export);
	rl_clear_history();
}

void	free_t_pipe(t_pipe *info)
{
	int	i;

	i = 0;
	while (i < info->size - 1)
		free(info->pipes[i++]);
	free(info->pipes);
	free(info->pid_list);
}

void	free_envp(t_exec *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
		free(data->envp[i++]);
	free(data->envp);
}

void	unlink_files(t_exec *data, t_cmd **input)
{
	t_cmd			*curr;
	t_output_input	*iterate;

	(void)data;
	curr = *input;
	while (curr)
	{
		iterate = curr->redirection;
		while (iterate)
		{
			if (iterate->heredoc_file != NULL)
				unlink(iterate->heredoc_file);
			iterate = iterate->next;
		}
		curr = curr->next;
	}
}
