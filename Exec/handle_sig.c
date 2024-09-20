/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:40:47 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/20 20:07:29 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_c(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void handle_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_c);
}
