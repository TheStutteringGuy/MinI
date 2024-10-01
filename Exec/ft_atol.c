/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:58:18 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/01 19:59:35 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long    ft_atol(char *str)
{
    unsigned long res;
    int sign;
    int i;

    res = 0;
    sign = 1;
    i = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
        i++;
    if (str[i] == '+')
        i++;
    if (str[i] == '-')
    {
        sign *= -1;
        i++;
    }
    while (ft_isdigit(str[i]))
    {
        res = res * 10 + (str[i] - 48);
        if ((sign == 1 && res > 9223372036854775807) || (sign == -1 && res > 9223372036854775808))
        {
            print_error("exit", str, "numeric argument required", 2);
            exit(2);
        }
        i++;
    }
    return (sign * res);
}
