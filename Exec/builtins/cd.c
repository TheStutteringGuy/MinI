/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/30 15:15:53 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void update_pwd_export(t_exec **list)
{
    char cwd[PATH_MAX];

    char *key;
    t_linked *iterate;

    getcwd(cwd, PATH_MAX);
    key = "PWD";
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

static void update_pwd(t_exec **list)
{
    char cwd[PATH_MAX];
    char *key;
    t_linked *iterate;

    getcwd(cwd, PATH_MAX);
    key = "PWD";
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
    update_pwd_export(list);
}

static void update_environ(t_exec **list, char *cwd)
{
    t_linked *iterate;

    iterate = (*list)->environ;
    while (iterate)
    {
        if (ft_strlen2(iterate->key) == ft_strlen2("OLDPWD") && ft_strncmp(iterate->key, "OLDPWD", ft_strlen2("OLDPWD")) == 0)
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
        if (ft_strlen2(iterate->key) == ft_strlen2("OLDPWD") && ft_strncmp(iterate->key, "OLDPWD", ft_strlen2("OLDPWD")) == 0)
        {
            free(iterate->value);
            iterate->value = ft_substr(cwd, 0, ft_strlen(cwd));
            break;
        }
        iterate = iterate->next;
    }
    update_pwd(list);
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
        last_exit_status = 1;
        return (-1);
    }
}

static int cd_home(t_exec *data, t_cmd *input)
{
    if (chdir(ft_getenv(data->environ, "HOME")) != 0)
    {
        print_error("cd", "HOME is not set", NULL, 1);
        last_exit_status = 1;
        return (0);
    }
    return (1);
}

static int cd_oldpwd(t_exec *data, t_cmd *input)
{
    if (chdir(ft_getenv(data->environ, "OLDPWD")) != 0)
    {
        print_error("cd", "OLDPWD is not set", NULL, 1);
        last_exit_status = 1;
        return (0);
    }
    return (1);
}

void cd_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    char cwd[PATH_MAX];

    getcwd(cwd, PATH_MAX);
    if (!input->arguments[0])
    {
        if (cd_home(data, input) == 0)
            return;
    }
    else
    {
        if (handle_arg(input) == -1)
            return;
        if (ft_strlen2(input->arguments[0]) == ft_strlen2("-") && ft_strncmp(input->arguments[0], "-", ft_strlen2(input->arguments[0])) == 0)
        {
            if (cd_oldpwd(data, input) == 0)
                return;
        }
        else if (chdir(input->arguments[0]) != 0)
        {
            print_error("cd", input->arguments[0], strerror(errno), 2);
            last_exit_status = 1;
            return;
        }
    }
    update_environ(&data, cwd);
}
