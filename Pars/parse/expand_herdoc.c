/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:02:15 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/09/20 23:23:06 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_pars.h"

char *expand_herdoc(char *str)
{
    char *res;
    char *env_value;
    size_t len;
    size_t i;
    size_t j;
    char temp[2];
    char *status_str;
    char *var_name;
    int index;

    len = ft_strlen(str);
    i = 0;
    res = (char *)malloc(1);
    if (!res)
        return (NULL);
    res[0] = '\0';
    while (i < len)
    {
        if (str[i] == '$')
        {
            if (str[i + 1] == '?')
            {
                status_str = ft_itoa(last_exit_status);
                res = ft_strjoin(res, status_str);
                free(status_str);
                i += 2;
            }
            else if (ft_isdigit(str[i + 1]))
            {
                index = i + 1;
                while (ft_isdigit(str[index]))
                    index++;
                res = ft_strjoin(res, str + index);
                break;
            }
            else
            {
                j = i + 1;
                while (j < len && (ft_isalnum(str[j]) || str[j] == '_'))
                    j++;
                var_name = ft_substr(str, i + 1, j - i - 1);
                env_value = getenv(var_name);
                free(var_name);
                if (env_value)
                    res = ft_strjoin(res, env_value);
                else
                    res = ft_strjoin(res, "");
                i = j;
            }
        }
        else if (str[i] == '\"')
        {
            i++;
            while (i < len && str[i] != '\"')
            {
                if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
                {
                    j = i + 1;
                    while (j < len && (ft_isalnum(str[j]) || str[j] == '_'))
                        j++;
                    var_name = ft_substr(str, i + 1, j - i - 1);
                    env_value = getenv(var_name);
                    free(var_name);
                    if (env_value)
                        res = ft_strjoin(res, env_value);
                    else
                        res = ft_strjoin(res, "");
                    i = j;
                }
                else
                {
                    temp[0] = str[i];
                    temp[1] = '\0';
                    res = ft_strjoin(res, temp);
                    i++;
                }
            }
            i++;
        }
        else
        {
            temp[0] = str[i];
            temp[1] = '\0';
            res = ft_strjoin(res, temp);
            i++;
        }
    }
    return (res);
}

