/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:09:42 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/07 22:52:23 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_w_r(int write_fd, int read_fd)
{
	if (read_fd != -1 && read_fd != 0)
		close(read_fd);
	if (write_fd != -1 && write_fd != 1)
		close(write_fd);
}

void	check_r(int read_fd)
{
	if (read_fd != -1 && read_fd != 0)
		close(read_fd);
}

void	check_w(int write_fd)
{
	if (write_fd != -1 && write_fd != 1)
		close(write_fd);
}
