/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:22 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/07 18:27:49 by thestutteri      ###   ########.fr       */
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
}
