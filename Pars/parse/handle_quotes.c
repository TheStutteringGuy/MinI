/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:18 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/12 16:35:22 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void malloc_error()
{
    printf("Error: malloc failed\n");
    exit(1);
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

void handle_quotes(char input, t_exec *exec)
{
    if (input == '"')
        exec->quote = 2;
    else
        exec->quote = 1;
    if (exec->delimiter == 0)
        exec->delimiter = input;
    else if (input == exec->delimiter)
    {
        exec->delimiter = 0;
    }
}

int count_values(const char *str)
{
    int count = 0;
    int in_value = 0;

    while (*str)
    {
        if (!ft_isspace(*str))
        {
            if (!in_value)
            {
                count++;
                in_value = 1;
            }
        }
        else
        {
            in_value = 0;
        }
        str++;
    }
    return count;
}

char *remove_space(const char *str)
{
    int i = 0;
    int j = 0;
    size_t length;

    if (str == NULL)
        return NULL;
    length = ft_strlen2(str);
    char *res = malloc(length + 1);
    if (res == NULL)
        return NULL;
    while (str[i] != '\0')
    {
        if (!ft_isspace(str[i]))
        {
            res[j] = str[i];
            j++;
        }
        i++;
    }
    res[j] = '\0';

    return res;
}

char *expand_env_var_string(char *input, int *i, t_exec *exec)
{
    char temp[3000];
    char *res;
    int j = 0;

    (*i)++;
    if (input[*i] == '\0' || !check_for_char(input[*i]))
    {
        return ft_strdup("$");
    }
    if (input[*i] == '?')
    {
        res = ft_itoa(g_last_exit_status);
        (*i)++;
        return res;
    }
    while (input[*i] && check_for_char(input[*i]))
    {
        temp[j++] = input[(*i)++];
    }
    temp[j] = '\0';
    res = expand(temp, exec);
    if (res == NULL)
        res = "\0";
    char *str;
    if (input[*i] == '$' && (input[*i + 1] == '\0' || ft_isspace(input[*i + 1])))
    {
        exec->quote = 2;
        res = ft_strjoin2(res, "$");
        return (res);
    }
    str = res;
    // if (input[*i] == '$' && input[*i + 1] == '\0')
    // {
    //     char *append = ft_strjoin2(str, "$");
    //     free(str);
    //     return (append);
    // }
    // if (input[*i] == '$')
    // {
    //     char *next_expansion = expand_env_var_string(input, i, exec);
    //     if (next_expansion)
    //     {
    //         char *combined = ft_strjoin2(str, next_expansion);
    //         free(str);
    //         free(next_expansion);
    //         return combined;
    //     }
    //     else
    //     {
    //         return str;
    //     }
    // }
    // else if (input[*i] == '$' && input[*i + 1] != '\0')
    // {
    //     while (input[*i] && check_for_char(input[*i]))
    //     {
    //         temp[j++] = input[(*i)++];
    //     }
    //     temp[j] = '\0';
    //     char *new_res = expand(temp, exec);
    //     char *new_str = remove_space(new_res);
    //     new_str = ft_strjoin2(str, new_str);
    //     return (new_str);
    // }
    // if (str == NULL)
    //     return NULL;
    return str;
}

static void handle_quote(char input, t_exec *exec)
{
    if (input == '"')
        exec->quote = 2;
    else
        exec->quote = 1;
    if (exec->delimiter == 0)
        exec->delimiter = input;
    else if (input == exec->delimiter)
    {
        exec->delimiter = 0;
    }
}

char *remove_quotes(char *input, t_exec *exec)
{
    int i = 0, j = 0;
    size_t input_len = ft_strlen2(input);
    char *str = malloc(3000 * sizeof(char));
    char *expanded;

    if (!str)
        return NULL;
    exec->delimiter = 0;
    exec->quote = 0;
    exec->not = 0;
    while (input[i] != '\0')
    {
        if ((input[i] == '\'' || input[i] == '"') && (exec->delimiter == 0 || input[i] == exec->delimiter) && exec->not == 0)
        {
            handle_quote(input[i], exec);
        }
        else if (input[i] == '$' && (exec->delimiter == 0 || exec->delimiter != '\'') && exec->not == 0)
        {
            expanded = expand_env_var_string(input, &i, exec);
            printf("expanded ----> %s\n", expanded);
            if (!expanded)
            {
                free(str);
                return NULL;
            }
            while (*expanded)
            {
                str[j++] = *expanded++;
            }
            if (input[i] == '$' && input[i + 1] == '\0')
                break;
            i--;
        }
        else
        {
            str[j++] = input[i];
        }
        i++;
    }
    str[j] = '\0';
    int count = count_values(str);
    if (count == 0 && exec->quote == 2)
        return (ft_strdup2(""));
    else if (count == 0)
        return (NULL);
    if (count >= 2)
    {
        if (exec->quote == 2)
        {
            return (str);
        }
        else
            return (NULL);
    }
    char *str1 = trim_spaces(str);
    return str1;
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
