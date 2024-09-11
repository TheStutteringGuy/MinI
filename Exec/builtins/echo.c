/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/07/31 01:59:44 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int  handle_flag(t_exec *data, t_cmd *input, int *flag)
{
    int i;
    size_t len;

    (void)data;
    len = ft_strlen2("-n");
    if (len != ft_strlen2(input->arguments[0]))
        return (0);
    if (len == ft_strlen2(input->arguments[0]) && ft_strncmp(input->arguments[0], "-n", ft_strlen2("-n")) != 0)
        return (0);
    *flag = 1;
    i = 1;
    while (input->arguments[i] != NULL)
    {
        if (len != ft_strlen2(input->arguments[i]))
            return (i);
        if (len == ft_strlen2(input->arguments[i]) && ft_strncmp(input->arguments[i], "-n", ft_strlen2("-n")) != 0) 
            return (i);
        ++i;
    }
    return (i);
}

void    echo_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    int stop;
    int flag;
    
    flag = 0;
    if (input->arguments)
    {
        stop = handle_flag(data, input, &flag);
        while (input->arguments[stop] != NULL)
        {
            printf("%s ", input->arguments[stop]);
            ++stop;
        }
    }
    if (flag == 0)
        printf("\n");
}