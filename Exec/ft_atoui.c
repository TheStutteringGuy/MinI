/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:51:04 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/27 14:22:14 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_atoui(char *str)
{
    int res;
    int i;
    int j;

    res = 0;
    i = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
        i++;
    if (str[i] == '-')
        return (-1);
    if (str[i] == '+')
        i++;
    while (ft_isdigit(str[i]))
    {
        res = res * 10 + (str[i] - 48);
        if (res >= 2147483647)
            return (-1);
        i++;
    }
    while(str[i] != '\0')
    {
        if ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
            i++;
        else
            return (0);
    }
    return (res);
}