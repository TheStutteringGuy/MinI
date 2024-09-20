/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/20 20:07:08 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void handle_arg(t_cmd *input)
{
    int i;

    i = 0;
    while (input->arguments[i] != NULL)
        ++i;
    if (i > 1)
    {
        printf("exit: too many arguments\n");
        exit(1);
    }
}

static void pars_arg(t_cmd *input)
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
            exit(1);
        }
        ++i;
    }
}

void exit_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    (void)data;
    printf("exit\n");
    if (input->arguments[0])
    {
        handle_arg(input);
        return;
        pars_arg(input);
        exit(ft_atoi(input->arguments[0]));
    }
    exit(last_exit_status);
}
