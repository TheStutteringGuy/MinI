/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/14 02:19:53 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env_simple(t_exec *data, t_cmd *input)
{
	t_linked	*iterat;

	(void)input;
	iterat = data->environ;
	while (iterat != NULL)
	{
		printf("%s=%s\n", iterat->key, iterat->value);
		iterat = iterat->next;
	}
	g_last_exit_status = 0;
}
