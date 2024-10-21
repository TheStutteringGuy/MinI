/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:02:12 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/21 23:17:58 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	malloc_error(void)
{
	printf("Error: malloc failed\n");
	exit(1);
}

char	*trim_spaces(char *str)
{
	while (ft_isspace((unsigned char)*str))
		str++;
	return (ft_strdup(str));
}

int	skip_whitespace(char *input, int i)
{
	while (input[i] && ft_isspace(input[i]))
		i++;
	return (i);
}
