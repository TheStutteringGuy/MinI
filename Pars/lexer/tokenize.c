/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:01 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/04 22:40:13 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function to create a new token
t_token *create_token(t_type type, char *value)
{
    t_token *new_token;

    if (value == NULL)
        return (NULL);
    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return (NULL);
    new_token->type = type;
    new_token->value = ft_strdup(value);
    new_token->next = NULL;
    return (new_token);
}

// Function to add a token to the end of the list
void add_token(t_token **head, t_token *new_token)
{
    t_token *current;

    if (!*head)
    {
        *head = new_token;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_token;
}

// Function to classify tokens and return the appropriate type
t_type classify_token(char *token, t_type expected)
{
    if (ft_strcmp(token, "|") == 0)
        return (PIPE);
    else if (ft_strcmp(token, "<") == 0)
        return (RED_IN);
    else if (ft_strcmp(token, ">") == 0)
        return (RED_OUT);
    else if (ft_strcmp(token, "<<") == 0)
        return (HERDOC);
    else if (ft_strcmp(token, ">>") == 0)
        return (APPEND);
    else
        return (expected);
}

// Function to handle the token by classifying and adding it to the list
void handle_token(t_token **token_list, char *token, t_type *expected)
{
    char *processed_token;
    char *expand_token;
    t_type type;
    t_token *new_token;

    processed_token = handle_incorrect_quotes(token);
    if (!processed_token)
    {
        write(2, "Syntax error: incorrect quotes\n", 32);
        return;
    }
    type = classify_token(processed_token, *expected);
    new_token = create_token(type, processed_token);
    if (new_token)
        add_token(token_list, new_token);
    if (type == PIPE)
        *expected = COMMAND;
    else if (type == COMMAND)
        *expected = ARGUMENT;
    free(processed_token);
}

void handle_quotes_and_delimiter(char input_char, t_exec *exec)
{
    if (input_char == '"')
        exec->quote = 2;
    else
        exec->quote = 1;
    if (exec->delimiter == 0)
        exec->delimiter = input_char;
    else if (input_char == exec->delimiter)
        exec->delimiter = 0;
}

void handle_token_if_needed(char *token_list, char *token, int *expected, int *token_len)
{
    if (*token_len > 0)
    {
        token[*token_len] = '\0';
        handle_token(token_list, token, expected);
        *token_len = 0;
    }
}
void increment_token(char *token, int *token_len, int *i, char *input)
{
    token[*token_len] = input[*i];
    (*token_len)++;
    (*i)++;
    token[*token_len] = input[*i];
    (*token_len)++;
    token[*token_len] = '\0';
}
void copy_var(char *input, int *i, int *j, char *temp)
{
    *j = 0;
    while (input[*i] && check_for_char(input[*i]))
    {
        temp[*j] = input[*i];
        (*i)++;
        (*j)++;
    }
    temp[*j] = '\0';
}

void copy_result(char *res, int *k, char *token, int *token_len)
{
    while (res[*k] != '\0')
    {
        token[*token_len] = res[*k];
        (*token_len)++;
        (*k)++;
    }
    token[*token_len] = '\0';
}

void copy_dollar(char *token, int *token_len)
{
    token[*token_len] = '$';
    (*token_len)++;
}

void increment_input(char *input, char *token, int *i, int *token_len)
{
    token[*token_len] = input[*i];
    (*token_len)++;
    (*i)++;
    token[*token_len] = '\0';
}

void process_token_if_needed(t_token **token_list, char *token, int *token_len, t_type *expected)
{
    if (*token_len > 0)
    {
        token[*token_len] = '\0';
        handle_token(token_list, token, expected);
        *token_len = 0;
    }
}

void process_final(t_token **token_list, char *token, t_type *expected, int *token_len)
{
    token[*token_len] = '\0';
    handle_token(token_list, token, expected);
}

// Main function to tokenize input
void tokenize_input(char *input, t_token **token_list, t_exec *exec)
{
    int i;
    int j;
    int k;
    char token[3000];
    int token_len;
    char temp[3000];
    char *res;
    t_type expected;
    size_t len;

    i = 0;
    len = ft_strlen2(input);
    token_len = 0;
    expected = COMMAND;
    res = malloc(len + 1);
    exec->delimiter = 0;
    exec->quote = 0;
    while (input[i] != '\0')
    {
        if ((input[i] == '\'' || input[i] == '"') && (exec->delimiter == 0 || input[i] == exec->delimiter))
            handle_quotes_and_delimiter(input[i], exec);
        else if (ft_isspace(input[i]) && exec->delimiter == 0)
            handle_token_if_needed(token_list, token, &expected, &token_len);
        else if (is_multi_operator(&input[i]) && exec->delimiter == 0)
        {
            handle_token_if_needed(token_list, token, &expected, &token_len);
            increment_token(token, &token_len, &i, input);
            handle_token(token_list, token, &expected);
            token_len = 0;
        }
        else if (input[i] == '$' && input[i + 1] == '?')
        {
            increment_token(token, &token_len, &i, input);
            handle_token(token_list, token, &expected);
            token_len = 0;
        }
        else if (is_operator(input[i]) && exec->delimiter == 0)
        {
            handle_token_if_needed(token_list, token, &expected, &token_len);
            increment_input(input, token, &i, &token_len);
            handle_token(token_list, token, &expected);
            token_len = 0;
        }
        else if (input[i] == '$' && (exec->delimiter == 0 || exec->delimiter != '\''))
        {
            if (exec->delimiter == 0 && exec->quote == 1)
                exec->quote = 2;
            while (input[i] == '$')
            {
                i++;
                copy_var(input, &i, &j, temp);
                res = expand(temp, exec);
                if (res && *res != '\0')
                {
                    k = 0;
                    if (input[i] == '$' && input[i + 1] == '\0')
                        copy_result(res, &k, token, &token_len);
                    else
                    {
                        k = 0;
                        while (res[k] != '\0')
                        {
                            if (ft_isspace(res[k]))
                            {
                                while (res[k] != '\0')
                                {
                                    if (ft_isspace(res[k]))
                                        process_token_if_needed(token_list, token, &token_len, &expected);
                                    else
                                        token[token_len++] = res[k];
                                    k++;
                                }
                                break;
                            }
                            else
                                token[token_len++] = res[k];
                            k++;
                        }
                    }
                }
                if (input[i] == '$' && check_for_char(input[i + 1]))
                    continue;
                else if (input[i] == '$' && input[i + 1] != '\0')
                    copy_dollar(token, &token_len);
                if (input[i] != '$')
                    break;
            }
            if (input[i] == '\0' && input[i - 1] == '$')
                copy_dollar(token, &token_len);
            i--;
        }
        else
            token[token_len++] = input[i];
        i++;
    }
    if (token_len > 0)
        process_final(token_list, token, &expected, &token_len);
}
