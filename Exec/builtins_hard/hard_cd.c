/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/23 05:36:31 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void update_environ(t_exec **list, char *cwd)
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
        print_error("cd: too many arguments", NULL, NULL, 0);
        exit(1);
    }
}

void cd_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    char cwd[PATH_MAX];

    getcwd(cwd, PATH_MAX);
    if (!input->arguments[0])
    {
        if (chdir(ft_getenv(data->environ, "HOME")) != 0)
        {
            print_error("cd", "HOME is not set", NULL, 1);
            exit(1);
        }
    }
    else
    {
        if (handle_arg(input) == -1)
            return;
        if (ft_strlen2(input->arguments[0]) == ft_strlen2("-") && ft_strncmp(input->arguments[0], "-", ft_strlen2(input->arguments[0])) == 0)
        {
            if (chdir(ft_getenv(data->environ, "OLDPWD")) != 0)
            {
                print_error("cd", "OLDPWD is not set", NULL, 1);
                exit(1);
            }
            update_environ(&data, cwd);
            return;
        }
        if (chdir(input->arguments[0]) != 0)
        {
            print_error("cd", input->arguments[0], strerror(errno), 2);
            exit(1);
        }
    }
    update_environ(&data, cwd);
}
