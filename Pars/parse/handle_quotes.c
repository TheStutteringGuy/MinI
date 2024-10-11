/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:18 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/11 22:32:33 by thestutteri      ###   ########.fr       */
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
    if (count == 0)
        return (NULL);
    else if (count >= 2)
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

// char *remove_quotes(char *token, t_exec *exec)
// {
//     size_t len;
//     char *new_token;
//     int i;
//     int j;
//     char current_quote;
//     int env_start;
//     char *env_var;
//     char *env_value;
//     char *temp;

//     if (!token || !exec)
//         return NULL;
//     len = ft_strlen(token);
//     new_token = malloc(3000 * sizeof(char));
//     if (!new_token)
//     {
//         printf("Error: malloc failed\n");
//         exit(1);
//     }
//     i = 0;
//     j = 0;
//     current_quote = '\0';
//     while (i < len)
//     {
//         if (exec->flag == 1)
//             return (ft_strdup2(token));
//         else if ((token[i] == '"' || token[i] == '\'') && current_quote == '\0')
//         {
//             current_quote = token[i];
//             i++;
//         }
//         else if (token[i] == current_quote)
//         {
//             current_quote = '\0';
//             i++;
//         }
//         else if (token[i] == '$')
//         {
//             if (current_quote != '\'')
//             {
//                 if (i + 1 < len && (ft_isalnum(token[i + 1]) || token[i + 1] == '_'))
//                 {
//                     i++;
//                     env_start = i;
//                     while (i < len && (ft_isalnum(token[i]) || token[i] == '_' || token[i] == '?'))
//                         i++;
//                     env_var = ft_substr(token, env_start, i - env_start);
//                     env_value = ft_getexport(exec->export, env_var);
//                     printf("here --> %s\n", env_value);
//                     free(env_var);
//                     if (env_value == NULL)
//                     {
//                         continue;
//                     }
//                     size_t env_len = ft_strlen(env_value);
//                     char *space = ft_strchr(env_value, ' ');
//                     printf("space---> %s\n", space);
//                     if (space)
//                     {
//                         char *next_value = space + 1;
//                         while (*next_value && ft_isspace(*next_value))
//                             next_value++;
//                         if (*next_value != '\0' && !(i < len && token[i] == '$' && (i + 1 == len || token[i + 1] == '\0')))
//                         {
//                             free(new_token);
//                             return NULL;
//                         }
//                     }
//                     if (i < len && token[i] == '$' && (i + 1 == len || token[i + 1] == '\0'))
//                     {
//                         temp = malloc(j + env_len + 2);
//                         if (!temp)
//                         {
//                             printf("Error: malloc failed\n");
//                             exit(1);
//                         }
//                         if (j > 0)
//                         {
//                             ft_memcpy(temp, new_token, j);
//                         }
//                         ft_memcpy(&temp[j], env_value, env_len);
//                         temp[j + env_len] = '$';
//                         j += env_len + 1;
//                         temp[j] = '\0';
//                         free(new_token);
//                         new_token = temp;
//                         i++;
//                     }
//                     else
//                     {
//                         ft_memcpy(&new_token[j], env_value, env_len);
//                         j += env_len;
//                     }
//                 }
//                 else if (i + 1 < len && token[i + 1] == '?')
//                 {
//                     i += 2;
//                     char *str = ft_itoa(g_last_exit_status);
//                     size_t str_len = ft_strlen(str);
//                     ft_memcpy(&new_token[j], str, str_len);
//                     j += str_len;
//                     free(str);
//                 }
//                 else
//                 {
//                     new_token[j++] = '$';
//                     i++;
//                 }
//             }
//             else
//             {
//                 new_token[j++] = '$';
//                 i++;
//             }
//         }
//         else if (token[i] == '\\' && current_quote == '"')
//         {
//             i++;
//             if (i < len)
//             {
//                 new_token[j++] = token[i++];
//             }
//         }
//         else
//         {
//             new_token[j++] = token[i++];
//         }
//     }
//     new_token[j] = '\0';
//     return new_token;
// }

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
