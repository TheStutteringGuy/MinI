/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/14 02:34:00 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_arg_1(t_exec *data, char *str)
{
	(void)data;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
	{
		print_error("export", str, "not a valid identifier", 2);
		g_last_exit_status = 1;
		return (-1);
	}
	return (1);
}

static int	handle_arg_4_(t_exec *data, char *str, int j)
{
	while (str[j] != '+')
	{
		if (ft_isalpha(str[j]) == 0 && ft_isdigit(str[j]) == 0 && str[j] != '_')
		{
			print_err(data, str);
			return (-1);
		}
		j++;
	}
	return (0);
}

static int	handle_arg_3(t_exec *data, char *str, int flag, int j)
{
	if (flag == 1)
	{
		while (str[j] != '=')
		{
			if (ft_isalpha(str[j]) == 0 && ft_isdigit(str[j]) == 0
				&& str[j] != '_')
			{
				print_err(data, str);
				return (-1);
			}
			j++;
		}
		return (0);
	}
	while (str[j] != '\0')
	{
		if (ft_isalpha(str[j]) == 0 && ft_isdigit(str[j]) == 0 && str[j] != '_')
		{
			print_err(data, str);
			return (-1);
		}
		j++;
	}
	return (0);
}

static int	handle_arg(t_exec *data, char *str, int *flag, t_cmd *input)
{
	int	j;

	(void)input;
	if (handle_arg_1(data, str) == -1)
		return (-1);
	j = 1;
	handle_arg_2(str, flag, j);
	if (*flag == 1)
		handle_arg_4(data, str, flag, j);
	if (*flag == 2)
	{
		if (handle_arg_4_(data, str, j) == -1)
			return (-1);
	}
	else
	{
		if (handle_arg_3(data, str, *flag, j) == -1)
			return (-1);
	}
	return (0);
}

void	export_simple(t_exec *data, t_cmd *input)
{
	int	flag;
	int	i;

	i = -1;
	g_last_exit_status = 0;
	if (input->arguments[0])
	{
		while (input->arguments[++i])
		{
			flag = 0;
			if (handle_arg(data, input->arguments[i], &flag, input) == 0)
			{
				if (flag == 1)
					handle_equal(data, input->arguments[i]);
				else if (flag == 0)
					handle_not(data, input->arguments[i]);
				else if (flag == 2)
					handle_plus(data, input->arguments[i]);
			}
		}
		return ;
	}
	sort_list(&data->export);
	print_value(data->export);
}
