/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:33:35 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/13 02:16:27 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execve_handle_hard(t_exec *data, t_cmd *input, int read_fd,
		int write_fd)
{
	int	i;

	(void)read_fd;
	(void)write_fd;
	i = list_size(data->environ);
	data->envp = malloc(sizeof(char *) * (i + 1));
	data->envp[i] = NULL;
	turn(data->envp, data->environ);
	child_function(data, input);
}
