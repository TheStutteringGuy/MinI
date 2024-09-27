/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:51:04 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/27 11:59:49 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned int    ft_atoui(char *str)
{
    unsigned int res;
    int i;
    int j;

    res = 0;
    i = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
        i++;
    if (str[i] == '-')
        return (0);
    if (str[i] == '+')
        i++;
    while (ft_isdigit(str[i]))
    {
        res = res * 10 + (str[i] - 48);
        i++;
    }
    while(str[i] != '\0')
    {
        if (!ft_isdigit(str[i]) || (str[i] < 9 && str[i] > 13) || str[i] != ' ')
            return (0);
        i++;
    }
    return (res);
}