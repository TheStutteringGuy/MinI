/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:29 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/09/20 01:20:30 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_pars.h"

char *ft_strcpy(char *dest, const char *src)
{
    char *dest_start = dest;

    while ((*dest++ = *src++))
        ;

    return dest_start;
}
