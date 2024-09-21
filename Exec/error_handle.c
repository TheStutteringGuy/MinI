/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 01:39:52 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/21 01:48:45 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    print_error(char *s1, char *s2, int value)
{
    int saved_fd;
    
    saved_fd = dup(STDOUT_FILENO);
    dup2(2, STDOUT_FILENO);
    if (value == 0)
        printf("%s\n", s1);
    else if (value == 1)
        printf("%s: %s\n", s1, s2);
    dup2(saved_fd, STDERR_FILENO);
}