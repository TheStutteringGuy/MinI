/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 01:43:04 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/19 17:09:50 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *s1)
{
	int	saved_fd;

	saved_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("syntax error near unexpected token `%s`\n", s1);
	dup2(saved_fd, STDOUT_FILENO);
	close(saved_fd);
}
