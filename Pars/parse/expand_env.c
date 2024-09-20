/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:13 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/09/20 01:20:14 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_pars.h"

char *expand_env_var(char *token)
{
    char *env_var;
    char *env_value;

    if (token[0] == '$')
    {
        if (ft_strcmp(token, "$?") == 0)
            return (ft_itoa(last_exit_status));
        if (ft_isdigit(token[1]))
            return (ft_strdup(token + 2));
        else
        {
            printf("Invalid env: %s\n", env_var);
            return (ft_strdup(""));
        }
    }
    return (ft_strdup(token));
}
