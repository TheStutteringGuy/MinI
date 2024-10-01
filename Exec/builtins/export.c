/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/01 20:23:55 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void ft_swap(t_linked *list1, t_linked *list2)
{
    char *tmp_key;
    char *tmp_value;
    int tmp_flag;

    tmp_key = list1->key;
    list1->key = list2->key;
    list2->key = tmp_key;

    tmp_value = list1->value;
    list1->value = list2->value;
    list2->value = tmp_value;
    
    tmp_flag = list1->flag;
    list1->flag = list2->flag;
    list2->flag = tmp_flag;
}

static void sort_list(t_linked **list)
{
    t_linked *iterat;
    t_linked *iterat2;
    size_t len;

    iterat = *list;
    while (iterat)
    {
        iterat2 = iterat->next;
        while (iterat2)
        {
            len = ft_strlen2(iterat->key);
            if (len < ft_strlen2(iterat2->key))
                len = ft_strlen2(iterat2->key);
            if (ft_strncmp(iterat->key, iterat2->key, len) > 0)
                ft_swap(iterat, iterat2);
            iterat2 = iterat2->next;
        }
        iterat = iterat->next;
    }
}

static void print_err(t_exec *data,char *str)
{
    print_error("export", str, "not a valid identifier", 2);
    *data->last_exit_status  = 1;
}

static int handle_arg_1(t_exec *data, char *str)
{
    if (ft_isalpha(str[0]) == 0 && str[0] != '_')
    {
        print_error("export", str, "not a valid identifier", 2);
        *data->last_exit_status  = 1;
        return (-1);
    }
    return (1);
}

static void handle_arg_2(char *str, int *flag, int j)
{
    while (str[j] != '\0')
    {
        if (str[j] == '=')
            *flag = 1;
        j++;
    }
}

static int handle_arg_3(t_exec *data,char *str, int flag, int j)
{
    if (flag == 1)
    {
        while (str[j] != '=')
        {
            if (ft_isalpha(str[j]) == 0 && ft_isdigit(str[j]) == 0 && str[j] != '_')
            {
                print_err(data, str);
                return (-1);
            }
            j++;
        }
    }
    else
    {
        while (str[j] != '\0')
        {
            if (ft_isalpha(str[j]) == 0 && ft_isdigit(str[j]) == 0 && str[j] != '_')
            {
                print_err(data, str);
                return (-1);
            }
            j++;
        }
    }
}

static int handle_arg(t_exec *data, char *str, int *flag, t_cmd *input)
{
    int j;

    if (handle_arg_1(data, str) == -1)
        return (-1);
    j = 1;
    handle_arg_2(str, flag, j);
    if (handle_arg_3(data, str, *flag, j) == -1)
        return (-1);
}

static void see_if_it_exist(t_exec *data, char *str)
{
    t_linked *iterate;

    iterate = data->export;
    if (ft_get_export(iterate, str) == 1)
    {
        remove_list(&data->environ, str);
        remove_list(&data->export, str);
        free(str);
        return;
    }
    free(str);
}

static void handle_equal(t_exec *data, char *str)
{
    int i;
    int j;
    int y;
    int z;

    i = 0;
    while (str[i] != '=')
        i++;
    j = i;
    z = j + 1;
    y = 0;
    if (str[i + 1] == '\"')
    {
        y -= 1;
        z++;
    }
    i = z;
    while (str[i++] != '\0')
        y++;
    see_if_it_exist(data, ft_substr(str, 0, j));
    create_node(&data->environ, ft_substr(str, 0, j), ft_substr(str, z, y), 1);
    create_node(&data->export, ft_substr(str, 0, j), ft_substr(str, z, y), 1);
}

static void handle_not(t_exec *data, char *str)
{
    see_if_it_exist(data, ft_substr(str, 0, ft_strlen2(str)));
    create_node(&data->export, ft_substr(str, 0, ft_strlen2(str)), ft_substr(str, 0, 0), 0);
}

static void print_value(t_linked *list)
{
    while (list)
    {
        if (list->flag == 0)
            printf("declare -x %s %d\n", list->key, list->flag);
        else
        {
            if (*list->value != '\0')
                printf("declare -x %s=\"%s\" %d\n", list->key, list->value, list->flag);
            if (*list->value == '\0')
                printf("declare -x %s=\"%s\" %d\n", list->key, list->value, list->flag);
        }
        list = list->next;
    }
}

void export_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    t_linked *list;
    int flag;
    int i;

    flag = 0;
    i = 0;
    if (input->arguments[0])
    {
        while (input->arguments[i])
        {
            if (handle_arg(data, input->arguments[i], &flag, input) == -1)
                return;
            printf("%d\n", flag);
            if (flag == 1)
                handle_equal(data, input->arguments[i]);
            else if (flag == 0)
                handle_not(data, input->arguments[i]);
            ++i;
        }
        return;
    }
    sort_list(&data->export);
    list = data->export;
    print_value(list);
}
