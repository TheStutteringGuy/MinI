/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:51:17 by thestutteri       #+#    #+#             */
/*   Updated: 2024/09/21 01:52:29 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void clear_list(t_linked **list)
{
    t_linked *iterate;
    t_linked *tmp;

    iterate = *list;
    while (iterate)
    {
        tmp = iterate;
        iterate = iterate->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
    *list = NULL;
}

void add_front(t_linked **list, t_linked *new)
{
    new = *list;
    *list = new;
}

void add_back(t_linked **list, t_linked *new)
{
    t_linked *iterat;

    iterat = *list;
    while (iterat->next != NULL)
        iterat = iterat->next;
    iterat->next = new;
}

void create_node(t_linked **list, char *key, char *value, int flag)
{
    t_linked *new;

    if (list == NULL)
    {
        print_error("It is Null\n", NULL, 0);
        exit(1);
    }
    new = malloc(sizeof(t_linked));
    new->key = key;
    new->value = value;
    new->next = NULL;
    if (*list == NULL)
    {
        *list = new;
        return;
    }
    if (flag == 0)
        add_front(list, new);
    else
        add_back(list, new);
}