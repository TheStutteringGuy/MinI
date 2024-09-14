/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/07/31 01:59:25 by thestutteri      ###   ########.fr       */
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
        printf("cd: too many arguments\n");
        exit(1);
    }
}

void    cd_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    char cwd[PATH_MAX];

    (void)data;
    if (input->arguments[0])
    {
        handle_arg(input);
        if (chdir(input->arguments[0]) != 0)
        {
            printf("cd: %s: %s\n", input->arguments[0], strerror(errno));
            exit(1);
        }
    }
    getcwd(cwd, PATH_MAX);
    printf("%s\n", cwd);
}
