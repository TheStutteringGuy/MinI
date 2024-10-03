/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:33:35 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/03 19:24:06 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char **case_one(char *str)
{
    char **arg;

    arg = malloc(sizeof(char *) * 2);
    if (!arg)
    {
        print_error("Failed to allocate arg", NULL, NULL, 0);
        exit(1);
    }
    arg[0] = ft_substr(str, 0, ft_strlen2(str));
    arg[1] = NULL;
    return (arg);
}

static char **join_to_array(char *str, char **array)
{
    int total;
    int i;
    int j;
    char **argv;

    if (array == NULL)
    {
        argv = case_one(str);
        return (argv);
    }
    total = 0;
    while (array[total])
        total++;
    ++total;
    argv = malloc(sizeof(char *) * (total + 1));
    if (!argv)
    {
        print_error("Failed to allocate arg", NULL, NULL, 0);
        exit(0);
    }
    argv[total] = NULL;
    argv[0] = ft_substr(str, 0, ft_strlen2(str));
    j = 0;
    i = 1;
    while (array[j])
    {
        argv[i] = ft_substr(array[j], 0, ft_strlen2(array[j]));
        i++;
        j++;
    }
    return (argv);
}

static void ft_acces(t_exec *data, t_cmd *input)
{
    errno = 0;
    if (access(input->command, F_OK | X_OK) == 0)
    {
        data->arg = join_to_array(input->command, input->arguments);
        execve(input->command, data->arg, data->envp);
    }
    else
    {
        print_error(input->command, strerror(errno), NULL, 1);
        if (errno == ENOENT)
            exit(127);
        if (errno == EACCES)
            exit(126);
    }
    exit(0);
}

static void ft_handle_function(char *str, int *flag)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '/')
            *flag = 1;
        i++;
    }
}

static void child_funtion_2(t_exec *data, t_cmd *input, char *inp)
{
    int i;
    char **split;
    char *join;
    char *check;
    
    i = 0;
    split = ft_split(inp, ':');
    while (split[i])
    {
        join = ft_strjoin2(split[i], "/");
        check = ft_strjoin2(join, input->command);
        free(join);
        if (access(check, F_OK | X_OK) == 0)
        {
            data->arg = join_to_array(input->command, input->arguments);
            execve(check, data->arg, data->envp);
        }
        free(check);
        i++;
    }
    print_error(input->command, "command not found\n", NULL, 1);
    exit(127);
}

static void child_function(t_exec *data, t_cmd *input)
{
    int flag;
    char *inp;
    
    inp = ft_substr("", 0, 0);
    flag = 0;
    ft_handle_function(input->command, &flag);
    if (flag == 1)
        ft_acces(data, input);
    inp = ft_getenv(data->export, "PATH");
    if (inp == NULL)
        return;
    child_funtion_2(data, input, inp);
}

static void turn(char **envp, t_linked *list)
{
    char *join;
    int j;

    j = 0;
    while (list)
    {
        join = ft_strjoin2(list->key, "=");
        envp[j] = ft_strjoin2(join, list->value);
        free(join);
        j++;
        list = list->next;
    }
}

void execve_handle_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    pid_t id;
    int i;
    int status;

    i = list_size(data->environ);
    data->envp = malloc(sizeof(char *) * (i + 1));
    data->envp[i] = NULL;
    turn(data->envp, data->environ);
    child_function(data, input);
}
