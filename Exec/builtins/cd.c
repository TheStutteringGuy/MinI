/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/16 20:50:34 by thestutteri      ###   ########.fr       */
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
        printf("cd: too many arguments\n");
        last_exit_status = 1;
        return (-1);
    }
}

void    cd_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    char cwd[PATH_MAX];

    (void)data;
    if (input->arguments[0])
    {
        if (handle_arg(input) == -1)
            return ;
        if (chdir(input->arguments[0]) != 0)
        {
            printf("cd: %s: %s\n", input->arguments[0], strerror(errno));
            last_exit_status = 1;
            return ;
        }
    }
    getcwd(cwd, PATH_MAX);
    printf("%s\n", cwd);
}
