/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 02:03:04 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/14 07:43:53 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_everything(t_exec *data, t_cmd *input)
{
	(void)input;
	clear_list(&data->environ);
	free(data->environ);
	clear_list(&data->export);
	free(data->export);
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

void	unlink_files(t_cmd **input)
{
	t_cmd			*curr;
	t_output_input	*iterate;

	curr = *input;
	while (curr)
	{
		iterate = curr->redirection;
		unlink(iterate->filename);
		curr = curr->next;
	}
}