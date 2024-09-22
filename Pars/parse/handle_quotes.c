/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:18 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/09/22 16:01:48 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function to handle double quotes
char *remove_quotes(char *token)
{
    size_t len;
    char *new_token;
    int i, j;
    char current_quote;
    int env_start;
    char *env_var;
    char *env_value;
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
        // Handle cases like $'...'$
        if (token[i] == '$' && (i + 1 < len) && (token[i + 1] == '\'' || token[i + 1] == '"'))
        {
            current_quote = token[i + 1];
            i += 2; // Skip $ and the opening quote
            if (current_quote == '\'')
            {
                // Preserve everything within $'...'$
                while (i < len && token[i] != current_quote)
                    new_token[j++] = token[i++];
            }
            else if (current_quote == '"')
            {
                // Expand variables within $"..."$
                while (i < len && token[i] != current_quote)
                {
                    if (token[i] == '$')
                    {
                        i++;
                        env_start = i;
                        while (i < len && (ft_isalnum(token[i]) || token[i] == '_' || token[i] == '?'))
                            i++;
                        env_var = ft_substr(token, env_start, i - env_start);
                        env_value = getenv(env_var);
                        free(env_var);
                        if (env_value)
                        {
                            env_len = ft_strlen(env_value);
                            memcpy(new_token + j, env_value, env_len);
                            j += env_len;
                        }
                    }
                    else if (token[i] == '\\' && i + 1 < len)
                    {
                        // Handle escaped characters within $"..."$
                        new_token[j++] = token[++i];
                    }
                    else
                    {
                        new_token[j++] = token[i++];
                    }
                }
            }
            if (i < len && token[i] == current_quote)
                i++; // Skip the closing quote
            if (i < len && token[i] == '$')
                new_token[j++] = token[i++]; // Preserve the trailing $
        }
        // Regular quotes processing
        else if ((token[i] == '"' || token[i] == '\'') && current_quote == '\0')
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
            // Check for standalone '$'
            if (i + 1 >= len || !(ft_isalnum(token[i + 1]) || token[i + 1] == '_'))
            {
                new_token[j++] = token[i++]; // Copy the standalone '$'
            }
            else
            {
                // Expand environment variable
                i++;
                env_start = i;
                while (i < len && (ft_isalnum(token[i]) || token[i] == '_' || token[i] == '?'))
                    i++;
                env_var = ft_substr(token, env_start, i - env_start);
                env_value = getenv(env_var);
                free(env_var);
                if (env_value)
                {
                    env_len = ft_strlen(env_value);
                    memcpy(new_token + j, env_value, env_len);
                    j += env_len;
                }
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
