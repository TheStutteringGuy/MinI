/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_simple_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 23:28:44 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/22 02:03:34 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_handle_function(char *str, int *flag)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			*flag = 1;
		i++;
	}
}

static void	free_child_2(t_exec *data, t_cmd *input, char **split)
{
	print_error(input->command, "command not found", NULL, 1);
	free_split(split);
	if (data->arg)
		free_split(data->arg);
	free_split(data->envp);
	free_everything(data, input);
}

void	child_funtion_2(t_exec *data, t_cmd *input, char *inp)
{
	int		i;
	char	**split;
	char	*join;
	char	*check;

	i = 0;
	data->arg = NULL;
	split = ft_split(inp, ':');
	while (split[i])
	{
		join = ft_strjoin2(split[i], "/");
		check = ft_strjoin2(join, input->command);
		free(join);
		if (access(check, F_OK | X_OK) == 0)
		{
			data->arg = join_to_array(input->command, input->arguments);
			execve(check, data->arg, data->envp);
			free(check);
			break ;
		}
		free(check);
		i++;
	}
	free_child_2(data, input, split);
	exit(127);
}

void	child_function(t_exec *data, t_cmd *input)
{
	int		flag;
	char	*inp;

	flag = 0;
	ft_handle_function(input->command, &flag);
	inp = ft_getenv(data->export, "PATH");
	if (flag == 1 || inp == NULL)
		ft_acces(data, input);
	child_funtion_2(data, input, inp);
}

void	turn(char **envp, t_linked *list)
{
	char	*join;
	int		j;

	j = 0;
	while (list)
	{
		join = ft_strjoin2(list->key, "=");
		envp[j] = ft_strjoin2(join, list->value);
		free(join);
		j++;
		list = list->next;
	}
}
