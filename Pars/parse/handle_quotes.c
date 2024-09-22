/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlaqqa <aahlaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:18 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/09/22 01:54:38 by aahlaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function to handle double quotes
char *remove_quotes(char *token)
{
    size_t len;
    char *new_token;
    int i;
    int j;
    char current_quote;
    int env_start;
    char *env_var;
    char *env_value;
    char *str;
    size_t env_len;
    char *temp;

    len = ft_strlen(token);
    new_token = malloc(len + 1);
    if (!new_token)
    {
        printf("Error: malloc failed\n");
        exit(1);
    }
    i = 0;
    j = 0;
    current_quote = '\0';
    while (i < len)
    {
        if ((token[i] == '"' || token[i] == '\'') && current_quote == '\0')
        {
            current_quote = token[i];
            i++;
        }
        else if (token[i] == current_quote)
        {
            current_quote = '\0';
            i++;
        }
        else if (token[i] == '$' && current_quote != '\'')
        {
            i++;
            env_start = i;
            while (i < len && (ft_isalnum(token[i]) || token[i] == '_' || token[i] == '?'))
                i++;
            env_var = ft_substr(token, env_start, i - env_start);
            if (ft_isdigit(env_var[0]))
                return (ft_strdup(env_var + 1));
            if (env_var[0] == '?' && env_var[1] == '\0')
                return (ft_itoa(last_exit_status));
            else if (env_var[0] == '?' && env_var[1] != '\0')
            {
                str = ft_itoa(last_exit_status);
                env_var[0] = str[0];
                return (env_var);
            }
            env_value = getenv(env_var);
            if (env_value == NULL)
            {
                free(env_var);
                free(new_token);
                return (NULL);
            }
            free(env_var);
            if (env_value)
            {
                env_len = ft_strlen(env_value);
                temp = malloc(j + env_len + 1);
                if (!temp)
                {
                    printf("Error: malloc failed\n");
                    exit(1);
                }
                if (j > 0)
                {
                    ft_memcpy(temp, new_token, j);
                }
                ft_memcpy(&temp[j], env_value, env_len);
                j += env_len;
                temp[j] = '\0';
                free(new_token);
                new_token = temp;
            }
        }
        else if (token[i] == '\\' && current_quote == '"')
        {
            i++;
            if (i < len)
            {
                new_token[j++] = token[i++];
            }
        }
        else
        {
            new_token[j++] = token[i++];
        }
    }
    new_token[j] = '\0';
    return new_token;
}

char *handle_incorrect_quotes(char *token)
{
    size_t len;
    int single_quotes;
    int double_quotes;
    size_t i;

    len = ft_strlen(token);
    single_quotes = 0;
    double_quotes = 0;
    i = 0;
    while (i < len)
    {
        if (token[i] == '\'')
            single_quotes++;
        else if (token[i] == '"')
            double_quotes++;
        i++;
    }
    if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
    {
        write(2, "Syntax error: unclosed quotes\n", 31);
        last_exit_status = 130;
        return (NULL);
    }
    return (ft_strdup(token));
}
