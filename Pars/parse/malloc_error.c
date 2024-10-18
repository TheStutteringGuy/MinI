/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:02:12 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/19 00:19:49 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	malloc_error(void)
{
	printf("Error: malloc failed\n");
	exit(1);
}

char *trim_spaces(char *str)
{
	while (ft_isspace((unsigned char)*str))
		str++;
	return (ft_strdup(str));
}
