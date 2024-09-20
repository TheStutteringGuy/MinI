/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/20 20:06:46 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void env_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
    t_linked *iterat;

    (void)input;
    iterat = data->environ;
    while (iterat != NULL)
    {
        printf("%s=%s\n", iterat->key, iterat->value);
        iterat = iterat->next;
    }
}