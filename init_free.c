/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:12:53 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/19 14:47:27 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_red(t_output_input *iterate)
{
	t_output_input	*tmp;

	while (iterate)
	{
		tmp = iterate;
		iterate = iterate->next;
		free(tmp->filename);
		free(tmp->delimiter);
		free(tmp->heredoc_file);
		free(tmp);
	}
}

void	free_everything_cmd(t_cmd **input)
{
	t_cmd	*iterate;
	t_cmd	*tmp;

	iterate = *input;
	while (iterate)
	{
		tmp = iterate;
		iterate = iterate->next;
		free(tmp->command);
		free_split(tmp->arguments);
		free_red(tmp->redirection);
		free(tmp);
	}
	*input = NULL;
}

void	free_everything_data(t_exec *data)
{
	clear_list(&data->environ);
	free(data->environ);
	clear_list(&data->export);
	free(data->export);
	rl_clear_history();
}

void	initialize_everything(t_exec *data, char **envp, char **av, int ac)
{
	(void)ac;
	data->environ = NULL;
	data->export = NULL;
	env_list(&data->environ, envp, av);
	update_shlvl(&data->environ);
	copy_environ(&data->export, data->environ);
	remove_list(&data->export, "_");
}
