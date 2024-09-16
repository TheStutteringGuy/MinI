/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/16 20:51:09 by thestutteri      ###   ########.fr       */
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
        printf("exit: too many arguments\n");
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
            printf("exit: %s: %s\n", input->arguments[0], "numeric argument required");
            last_exit_status = 1;
            return (-1);
        }
        ++i;
    }
}

void    exit_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    (void)data;
    printf("exit\n");
    if (input->arguments[0])
    {
        if (handle_arg(input) == -1)
            return ;
        if (pars_arg(input) == -1)
            return ;
        exit(ft_atoi(input->arguments[0]));
    }
    exit(last_exit_status);
}
