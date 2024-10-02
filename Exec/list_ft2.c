/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ft2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 01:39:55 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/02 18:13:08 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int list_size(t_linked *list)
{
    int i;
    t_linked *iterat;

    i = 0;
    iterat = list;
    while (iterat)
    {
        i++;
        iterat = iterat->next;
    }
    return (i);
}

static size_t key_return(char *key, char *key2)
{
    size_t len;

    len = ft_strlen2(key);
    if (len < ft_strlen2(key2))
        len = ft_strlen2(key2);
    return (len);
}

void delete_one(t_linked **list)
{
    t_linked *iterate;

    iterate = *list;
    *list = iterate->next;
    free(iterate->key);
    free(iterate->value);
    free(iterate);
    return;
}

void remove_list(t_linked **list, char *key)
{
    t_linked *iterate;
    t_linked *prev;
    size_t len;

    iterate = *list;
    len = key_return(iterate->key, key);
    if (ft_strncmp(iterate->key, key, len) == 0)
        return;
    prev = *list;
    iterate = (*list)->next;
    while (iterate)
    {
        len = key_return(iterate->key, key);
        if (ft_strncmp(iterate->key, key, len) == 0)
        {
            prev->next = iterate->next;
            free(iterate->key);
            free(iterate->value);
            free(iterate);
            return;
        }
        prev = prev->next;
        iterate = iterate->next;
    }
}

char *ft_getenv(t_linked *list, char *name)
{
    size_t len;

    while (list)
    {
        len = key_return(list->key, name);
        if (ft_strncmp(list->key, name, len) == 0)
            return (list->value);
        list = list->next;
    }
    return (NULL);
}

char *ft_getexport(t_linked *list, char *name)
{
    size_t len;

    while (list)
    {
        len = key_return(list->key, name);
        if (ft_strncmp(list->key, name, len) == 0)
            return (list->value);
        list = list->next;
    }
    return (NULL);
}

int ft_get_export(t_linked *list, char *name)
{
    size_t len;

    while (list)
    {
        len = key_return(list->key, name);
        if (ft_strncmp(list->key, name, len) == 0)
            return (1);
        list = list->next;
    }
    return (0);
}
