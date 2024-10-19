/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_me.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 21:48:50 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/19 21:57:41 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	check_flag_(char *str, int *flag)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]))
			*flag = 1;
		if (!ft_isspace(str[i]))
			break ;
		i++;
	}
}

static char	*check_me_spaces(char *str, t_exec *exec)
{
	int		flag;
	int		count;
	char	*res1;

	flag = 0;
	check_flag_(str, &flag);
	if (flag == 0)
	{
		count = count_values(str);
		if (count >= 2)
		{
			exec->expand = 1;
			return (ft_strdup2(str));
		}
		if (count == 1)
		{
			if (exec->expand != 1)
				exec->expand = 0;
			res1 = remove_space(str);
			return (res1);
		}
	}
	return (ft_strdup2(str));
}

char	*check_me(t_exec *exec, char *res)
{
	int		count;
	char	*res1;

	if (*res != '\0')
	{
		if (ft_isspace(*res))
		{
			exec->expand = 1;
			res1 = ft_strdup2(res);
			return (res1);
		}
		else
		{
			res1 = check_me_spaces(res, exec);
			return (res1);
		}
	}
	res1 = ft_strdup2(res);
	return (res1);
}