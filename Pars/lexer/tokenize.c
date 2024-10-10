/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:01 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/10 01:37:59 by thestutteri      ###   ########.fr       */
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
t_type classify_token(char *token, t_type expected, t_exec *exec)
{
    if ((ft_strcmp(token, "|") == 0) && exec->quote == 0)
        return (PIPE);
    else if ((ft_strcmp(token, "<") == 0) && exec->quote == 0)
        return (RED_IN);
    else if ((ft_strcmp(token, ">") == 0) && exec->quote == 0)
        return (RED_OUT);
    else if ((ft_strcmp(token, "<<") == 0) && exec->quote == 0)
        return (HERDOC);
    else if ((ft_strcmp(token, ">>") == 0) && exec->quote == 0)
        return (APPEND);
    else
        return (expected);
}

// Function to handle the token by classifying and adding it to the list
void handle_token(t_token **token_list, char *token, t_type *expected, t_exec *exec)
{
    char *processed_token;
    char *test;
    t_type type;
    t_token *new_token;

    processed_token = handle_incorrect_quotes(token);
    if (!processed_token)
    {
        write(2, "Syntax error: incorrect quotes\n", 32);
        return;
    }
    type = classify_token(processed_token, *expected, exec);
    new_token = create_token(type, processed_token);
    if (new_token)
        add_token(token_list, new_token);
    if (type == PIPE)
        *expected = COMMAND;
    else if (type == COMMAND)
        *expected = ARGUMENT;

    free(processed_token);
}

void handle_quote(char input, t_exec *exec)
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

void free_helpe(t_helpe *helpe)
{
    free(helpe->token);
    free(helpe->expected);
    free(helpe);
    return;
}

void copy_token(char *token, int *token_len, t_token **token_list, t_type expected, int *flag, t_exec *exec)
{
    if (*token_len > 0)
    {
        token[*token_len] = '\0';
        handle_token(token_list, token, &expected, exec);
        *flag = 0;
        *token_len = 0;
    }
}

void finalize_token(t_token **token_list, char *token, int *token_len, t_type expected, t_exec *exec)
{
    token[*token_len] = '\0';
    handle_token(token_list, token, &expected, exec);
    *token_len = 0;
}

void add_multi_operator(char *token, const char *input, int *token_len, int *i)
{
    token[(*token_len)++] = input[(*i)++];
    token[(*token_len)++] = input[*i];
}

void update_quote(t_exec *exec)
{
    if (exec->delimiter == 0 && exec->quote == 1)
        exec->quote = 2;
}

void append_dollar_and_handle(t_helpe *helpe, t_token **token_list, t_exec *exec)
{
    helpe->token[helpe->token_len++] = '$';
    helpe->token[helpe->token_len] = '\0';
    handle_token(token_list, helpe->token, helpe->expected, exec);
    helpe->token_len = 0;
}

void handle_dollar_at_end(char *res, t_helpe *helpe, t_token **token_list, t_exec *exec)
{
    int k = 0;

    while (res[k] != '\0')
        helpe->token[helpe->token_len++] = res[k++];
    append_dollar_and_handle(helpe, token_list, exec);
}

void handle_result_input(char *res, t_helpe *helpe, t_token **token_list, t_exec *exec)
{
    int k;

    k = 0;
    while (res[k] != '\0')
    {
        if (ft_isspace(res[k]))
        {
            if (helpe->token_len > 0)
            {
                helpe->token[helpe->token_len] = '\0';
                handle_token(token_list, helpe->token, helpe->expected, exec);
                helpe->token_len = 0;
            }
            while (ft_isspace(res[k]))
                k++;
        }
        else
            helpe->token[helpe->token_len++] = res[k++];
    }
}

void check_next_characters(char *input, t_helpe *helpe)
{
    if (input[helpe->i] == '$' && check_for_char(input[helpe->i + 1]))
        return;
    // else if (input[helpe->i] == '$' && input[helpe->i + 1] != '\0')
    //     helpe->token[helpe->token_len++] = '$';`
}

void handle_expansion_result(char *input, t_helpe *helpe, char *res, t_token **token_list, t_exec *exec)
{
    int is_dollar_at_end;
    int k;

    k = 0;
    is_dollar_at_end = 0;
    if (input[helpe->i] == '$' && input[helpe->i + 1] == '\0')
    {
        printf("1\n");
        while (res[k] != '\0')
            helpe->token[helpe->token_len++] = res[k++];
        helpe->token[helpe->token_len++] = '$';
        helpe->token[helpe->token_len] = '\0';
        handle_token(token_list, helpe->token, helpe->expected, exec);
        helpe->token_len = 0;
        helpe->i++;
        return ;
    }
    if (input[helpe->i] == '$' && (input[helpe->i + 1] == ' '))
    {
        printf("2\n");
        while (res[k] != '\0')
            helpe->token[helpe->token_len++] = res[k++];
        helpe->token[helpe->token_len++] = '$';
        helpe->token[helpe->token_len] = '\0';
        handle_token(token_list, helpe->token, helpe->expected, exec);
        helpe->token_len = 0;
        helpe->i++;
        return ;
    }
    if (input[helpe->i] == '$' && !check_for_char(input[helpe->i + 1]) && (input[helpe->i + 2] == '\0' || input[helpe->i + 2] == ' '))
    {
        printf("3\n");
      while (res[k] != '\0')
            helpe->token[helpe->token_len++] = res[k++];
        helpe->token[helpe->token_len++] = '$';
        helpe->token[helpe->token_len++] = input[helpe->i + 1];
        helpe->token[helpe->token_len] = '\0';
        handle_token(token_list, helpe->token, helpe->expected, exec);
        helpe->token_len = 0;
        helpe->i += 2;
        return ;  
    }
    if (res && *res != '\0')
    {
        printf("4\n");
        if (is_dollar_at_end)
        {
            handle_dollar_at_end(res, helpe, token_list, exec);
            return;
        }
        handle_result_input(res, helpe, token_list, exec);
    }
    check_next_characters(input, helpe);
}

void expand_env_var(char *input, t_helpe *helpe, t_token **token_list, t_exec *exec)
{
    char temp[3000];
    char *res;
    char *copy;
    int j;

    j = 0;
    exec->expand = 0;
    if (input[helpe->i] == '$')
    {
        (helpe->i)++;
        if (input[helpe->i] == '?')
        {
            res = ft_itoa(g_last_exit_status);
            if (res == NULL)
                exec->expand = 1;
            helpe->i++;
            handle_expansion_result(input, helpe, res, token_list, exec);
            free(res);
            return;
        }
        j = 0;
        while (input[helpe->i] && check_for_char(input[helpe->i]))
            temp[j++] = input[(helpe->i)++];
        temp[j] = '\0';
        res = expand(temp, exec);
        if (res == NULL)
            exec->expand = 1;
        handle_expansion_result(input, helpe, res, token_list, exec);
    }
}

t_helpe *initialize_helper(char *input)
{
    t_helpe *helpe;

    helpe = malloc(sizeof(t_helpe));
    if (!helpe)
        return NULL;
    helpe->i = 0;
    helpe->token_len = 0;
    helpe->token = malloc(3000 * sizeof(char));
    if (!helpe->token)
    {
        free(helpe);
        return NULL;
    }
    helpe->expected = malloc(sizeof(t_type));
    if (!helpe->expected)
    {
        free(helpe->token);
        free(helpe);
        return NULL;
    }
    *helpe->expected = COMMAND;
    return helpe;
}

void handle_operators_logic(char *input, t_helpe *helpe, t_token **token_list, int *flag, t_exec *exec)
{
    if (helpe->token_len > 0)
        finalize_token(token_list, helpe->token, &helpe->token_len, *helpe->expected, exec);
    if (is_multi_operator(&input[helpe->i]))
        add_multi_operator(helpe->token, input, &helpe->token_len, &helpe->i);
    else
        helpe->token[helpe->token_len++] = input[helpe->i];
    finalize_token(token_list, helpe->token, &helpe->token_len, *helpe->expected, exec);
    *flag = 1;
}

void finalize_tokens(t_helpe *helpe, t_token **token_list, t_exec *exec)
{
    if (helpe->token_len > 0)
    {
        helpe->token[helpe->token_len] = '\0';
        handle_token(token_list, helpe->token, helpe->expected, exec);
    }
}

void handle_dollar_sign_logic(char *input, t_helpe *helpe, t_token **token_list, t_exec *exec)
{
    update_quote(exec);
    if (input[helpe->i] == '$' && input[helpe->i + 1] == '\0')
    {
        helpe->token[helpe->token_len] = '$';
        helpe->token_len++;
        return;
    }
    if (input[helpe->i] == '$' && ft_isspace(input[helpe->i + 1]))
    {
        helpe->token[helpe->token_len] = '$';
        helpe->token_len++;
        return;
    }
    expand_env_var(input, helpe, token_list, exec);
    helpe->i--;
}

// Main function to tokenize input
void tokenize_input(char *input, t_token **token_list, t_exec *exec)
{
    t_helpe *helpe;

    helpe = initialize_helper(input);
    if (!helpe)
        return;
    exec->delimiter = 0;
    exec->quote = 0;
    exec->not = 0;
    while (input[helpe->i] != '\0')
    {
        if ((input[helpe->i] == '\'' || input[helpe->i] == '"') && (exec->delimiter == 0 || input[helpe->i] == exec->delimiter) && exec->not == 0)
            handle_quote(input[helpe->i], exec);
        else if (ft_isspace(input[helpe->i]) && exec->delimiter == 0)
            copy_token(helpe->token, &helpe->token_len, token_list, *helpe->expected, &exec->not, exec);
        else if ((is_operator(input[helpe->i]) || is_multi_operator(&input[helpe->i])) && exec->delimiter == 0)
            handle_operators_logic(input, helpe, token_list, &exec->not, exec);
        else if ((is_operator(input[helpe->i]) || is_multi_operator(&input[helpe->i])) && exec->delimiter != 0)
            helpe->token[helpe->token_len++] = input[helpe->i];
        else if (input[helpe->i] == '$' && (exec->delimiter == 0 || exec->delimiter != '\'') && exec->not == 0)
            handle_dollar_sign_logic(input, helpe, token_list, exec);
        else
            helpe->token[helpe->token_len++] = input[helpe->i];
        helpe->i++;
    }
    finalize_tokens(helpe, token_list, exec);
    free_helpe(helpe);
}
