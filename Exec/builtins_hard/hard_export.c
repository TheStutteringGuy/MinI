/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/15 22:53:27 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_swap(t_linked *list1, t_linked *list2)
{
    char *tmp_key;
    char *tmp_value;

    tmp_key = list1->key;
    list1->key = list2->key;
    list2->key = tmp_key;

    tmp_value = list1->value;
    list1->value = list2->value;
    list2->value = tmp_value;
}

void    sort_list(t_linked **list)
{
    t_linked *iterat;
    t_linked *iterat2;
    size_t  len;

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

static void handle_arg(char *str, int *flag, t_cmd *input)
{
    int j;

    if (ft_isalpha(str[0]) == 0 && str[0] != '_')
    {
        printf("export: `%s': not a valid identifier\n", str);
        exit(1);
    }
    j = 1;
    while (str[j] != '\0')
    {
        if (str[j] == '=')
            *flag = 1;
        j++;
    }
    j = 1;
    if (*flag == 1)
    {
        while (str[j] != '=')
        {
            if (ft_isalpha(str[j]) == 0 && ft_isdigit(str[j]) == 0 && str[j] != '_')
            {
                printf("export: `%s': not a valid identifier\n", str);
                exit(1);
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
                printf("export: `%s': not a valid identifier\n", str);
                *input->last_exit_status = 1;
                exit(1);
            }
            j++;
        }
    }
}

void    see_if_it_exist(t_exec *data, char *str)
{
    t_linked *iterate;

    iterate = data->export;
    if (ft_get_export(iterate, str) == 1)
    {
        remove_list(&data->environ, str);
        remove_list(&data->export, str);
        free(str);
        return ;
    }
    free(str);
}

void    handle_equal(t_exec *data, char *str)
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

void    handle_not(t_exec *data, t_linked **list, char *str)
{
    see_if_it_exist(data, ft_substr(str, 0, ft_strlen2(str)));
    create_node(list, ft_substr(str, 0, ft_strlen2(str)), ft_substr(str, 0, 0), 1);
}


void    export_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd)
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
            handle_arg(input->arguments[i], &flag, input);
            printf("%d\n", flag);
            if (flag == 1)
                handle_equal(data, input->arguments[i]);
            else
                handle_not(data, &data->export, input->arguments[i]);
            ++i;
        }
        return ;
    }
    sort_list(&data->export);
    list = data->export;
    while (list)
    {
        if (*list->value != '\0')
            printf("declare -x %s=\"%s\"\n", list->key, list->value);
        else
            printf("declare -x %s=\n", list->key);
        list = list->next;
    }
}
