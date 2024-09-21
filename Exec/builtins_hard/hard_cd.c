/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/21 01:20:58 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void update_environ(t_exec **list, char *cwd)
{
    char *key;
    t_linked *iterate;

    key = "OLDPWD";
    iterate = (*list)->environ;
    while (iterate)
    {
        if (ft_strlen2(iterate->key) == ft_strlen2(key) && ft_strncmp(iterate->key, key, ft_strlen2(key)) == 0)
        {
            free(iterate->value);
            iterate->value = ft_substr(cwd, 0, ft_strlen(cwd));
            break;
        }
        iterate = iterate->next;
    }
    iterate = (*list)->export;
    while (iterate)
    {
        if (ft_strlen2(iterate->key) == ft_strlen2(key) && ft_strncmp(iterate->key, key, ft_strlen2(key)) == 0)
        {
            free(iterate->value);
            iterate->value = ft_substr(cwd, 0, ft_strlen(cwd));
            break;
        }
        iterate = iterate->next;
    }
}

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

void cd_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    char cwd[PATH_MAX];

    if (input->arguments[0])
    {
        if (handle_arg(input) == -1)
            return;
        if (ft_strlen2(input->arguments[0]) == ft_strlen2("-") && ft_strncmp(input->arguments[0], "-", ft_strlen2(input->arguments[0])) == 0)
        {
            getcwd(cwd, PATH_MAX);
            if (chdir(ft_getenv(data->environ, "OLDPWD")) != 0)
            {
                printf("cd: %s: %s\n", input->arguments[0], strerror(errno));
                last_exit_status = 1;
                return;
            }
            update_environ(&data, cwd);
            return;
        }
        if (chdir(input->arguments[0]) != 0)
        {
            printf("cd: %s: %s\n", input->arguments[0], strerror(errno));
            last_exit_status = 1;
            return;
        }
    }
    getcwd(cwd, PATH_MAX);
    printf("%s\n", cwd);
}
