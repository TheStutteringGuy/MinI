/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:31:32 by thestutteri       #+#    #+#             */
/*   Updated: 2024/10/05 18:51:28 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void handle_join(t_exec *data, char *str)
{
    int i;
    int j;
    int y;
    int z;
    char *value;
    char *value_saved;
    char *str1;

    i = 0;
    while (str[i] != '+')
        i++;
    j = i;
    i += 2;
    z = i;
    y = 0;
    while (str[i++])
        y++;
    value = ft_getexport(data->export, ft_substr(str, 0, j));
    value_saved = ft_strdup2(value);
    str1 = ft_substr(str, z, y);
    see_if_it_exist(data, ft_substr(str, 0, j));
    create_node(&data->environ, ft_substr(str, 0, j), ft_strjoin2(value_saved, str1), 1);
    create_node(&data->export, ft_substr(str, 0, j), ft_strjoin2(value_saved, str1), 1);  
    free(str1);
    free(value_saved);
}
