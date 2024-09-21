/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/21 04:19:59 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int handle_arg(t_cmd *input)
{
    int i;

    i = 0;
    while (input->arguments[i] != NULL)
        ++i;
    if (i > 1)
    {
        print_error("exit", "too many arguments", NULL, 1);
        last_exit_status = 1;
        return (-1);
    }
}

static int pars_arg(t_cmd *input)
{
    int i;

    i = 0;
    if (input->arguments[0][i] == '+' || input->arguments[0][i] == '-')
        i++;
    while (input->arguments[0][i] != '\0')
    {
        if (ft_isdigit(input->arguments[0][i]) == 0)
        {
            print_error("exit", input->arguments[0], "numeric argument required", 2);
            exit (2);
        }
        ++i;
    }
}

void exit_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    (void)data;
    if (input->arguments[0])
    {
        pars_arg(input);
        if (handle_arg(input) == -1)
            return;
        exit(ft_atoi(input->arguments[0]));
    }
    exit(last_exit_status);
}
