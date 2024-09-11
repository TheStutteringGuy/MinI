/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/07/31 02:00:56 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    pwd_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    (void)data;
    (void)input;
    if (ft_getenv(data->environ, "PWD"))
        printf("%s\n", ft_getenv(data->environ, "PWD"));
}
