/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:18 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/07 01:40:44 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void malloc_error()
{
    printf("Error: malloc failed\n");
    exit(1);
}

char *check_string(char *input)
{
    char *str;
    char *result;
    size_t result_size;
    int last_status_len;

    if (input[0] == '$')
    {
        if (input[0] == '$' && input[1] == '\0')
            return (ft_strdup2(input));
        if (ft_isdigit(input[1]))
            return (ft_strdup2(input + 2));
        if (input[1] == '?' && input[2] == '\0')
            return (ft_itoa(g_last_exit_status));
        if (input[1] == '?' && input[2] != '\0')
        {
            str = ft_itoa(g_last_exit_status);
            last_status_len = ft_strlen(str);
            result_size = last_status_len + ft_strlen2(input + 2) + 1;
            result = malloc(result_size);
            if (!result)
                malloc_error();
            ft_strlcpy(result, str, result_size);
            ft_strlcat(result, input + 2, result_size);
            free(input);
            return (result);
        }
    }
    return (input);
}

int check_quotes(char *input, t_exec *exec)
{
    size_t len;

    len = ft_strlen2(input);
    if (exec->quote == 1)
        return (1);
    else if (exec->quote == 2)
        return (2);
    else
        return (0);
}

char *remove_quotes(char *token, t_exec *exec)
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
    size_t str_len;
    char *temp;

    if (!token || !exec)
        return NULL;
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
        if (exec->flag == 1)
            return (ft_strdup2(token));
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
        else if (token[i] == '$')
        {
            if (token[i] == '$' && (token[i + 1] == '\'' || token[i + 1] == '"'))
            {
                while (token[i] == '$')
                     i++;
            }
            else if (current_quote != '\'')
            {
                if (i + 1 < len && (ft_isalnum(token[i + 1]) || token[i + 1] == '_'))
                {
                    i++;
                    env_start = i;
                    while (i < len && (ft_isalnum(token[i]) || token[i] == '_' || token[i] == '?'))
                        i++;
                    env_var = ft_substr(token, env_start, i - env_start);
                    if (ft_isdigit(env_var[0]))
                    {
                        return (ft_strdup(env_var + 1));
                    }
                    if (env_var[0] == '?' && env_var[1] == '\0')
                    {
                        free(env_var);
                        return (ft_itoa(g_last_exit_status));
                    }
                    else if (env_var[0] == '?' && env_var[1] != '\0')
                    {
                        str = ft_itoa(g_last_exit_status);
                        env_var[0] = str[0];
                        return (env_var);
                    }
                    env_value = ft_getexport(exec->export, env_var);
                    free(env_var);
                    if (env_value == NULL)
                    {
                        free(new_token);
                        return (NULL);
                    }
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
                else if (i + 1 < len && token[i + 1] == '?')
                {
                    i += 2;
                    str = ft_itoa(g_last_exit_status);
                    str_len = ft_strlen(str);
                    ft_memcpy(&new_token[j], str, str_len);
                    j += str_len;
                    free(str);
                }
                else
                {
                    new_token[j++] = '$';
                    i++;
                }
            }
            else
            {
                new_token[j++] = '$';
                i++;
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
        g_last_exit_status = 130;
        return (NULL);
    }
    return (ft_strdup(token));
}
