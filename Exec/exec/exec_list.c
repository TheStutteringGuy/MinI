/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 23:15:55 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/06 20:17:49 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check___(char *key, char *str)
{
	return (ft_strlen2(key) == ft_strlen2(str) && ft_strncmp(key, str,
			ft_strlen2(str)) == 0);
}

static void	create_necess(t_linked **list, char **av, int *flags, char *cwd)
{
	if (flags[0] == 0)
		create_node(list, ft_substr("PWD", 0, ft_strlen2("PWD")), ft_substr(cwd,
				0, ft_strlen2(cwd)), 1);
	if (flags[1] == 0)
		create_node(list, ft_substr("SHLVL", 0, ft_strlen2("SHLVL")),
			ft_substr("0", 0, ft_strlen2("0")), 1);
	if (flags[2] == 0)
		create_node(list, ft_substr("_", 0, ft_strlen2("_")), ft_substr(av[0],
				0, ft_strlen2(av[0])), 1);
}

void	check_necess(t_linked **list, char **av)
{
	t_linked	*curr;
	int			flags[3];
	char		cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	flags[0] = 0;
	flags[1] = 0;
	flags[2] = 0;
	curr = *list;
	while (curr)
	{
		if (check___(curr->key, "PWD"))
			flags[0] = 1;
		if (check___(curr->key, "SHLVL"))
			flags[1] = 1;
		if (check___(curr->key, "_"))
			;
		flags[2] = 1;
		curr = curr->next;
	}
	create_necess(list, av, flags, cwd);
}

void	env_list(t_linked **list, char **envp, char **av)
{
	int	i;
	int	j;
	int	y;

	i = 0;
	while (envp[i] != NULL)
	{
		y = 0;
		j = 0;
		while (envp[i][j] != '=')
		{
			j++;
		}
		y = j + 1;
		create_node(list, ft_substr(envp[i], 0, j), ft_substr(envp[i], y,
				ft_strlen2(envp[i])), 1);
		i++;
	}
	check_necess(list, av);
}
