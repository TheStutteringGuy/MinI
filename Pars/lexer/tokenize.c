#include "../mini_pars.h"

// Function to create a new token
t_token *create_token(t_type type, char *value)
{
    t_token *new_token;

    if (value == NULL)
        return NULL;
    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->type = type;
    new_token->value = remove_quotes(value);
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
    if (token[0] == '$')
        return (ENV);
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
        printf("Syntax error: incorrect quotes\n");
        return;
    }
    type = classify_token(processed_token, *expected);
    if (type == ENV)
    {
        expand_token = expand_env_var(processed_token);
        new_token = create_token(type, expand_token);
        free(expand_token);
    }
    else
    {
        //processed_token = remove_quotes(processed_token);
        new_token = create_token(type, processed_token);
    }
    if (new_token)
        add_token(token_list, new_token);
    if (type == PIPE)
        *expected = COMMAND;
    else if (type == COMMAND)
        *expected = ARGUMENT;
    free(processed_token);
}

// Main function to tokenize input
void tokenize_input(char *input, t_token **token_list)
{
    int i;
    int in_quotes;
    char current_quote;
    char token[1024];
    int token_len;
    t_type expected;

    i = 0;
    in_quotes = 0;
    current_quote = '\0';
    token_len = 0;
    expected = COMMAND;
    while (input[i] != '\0')
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            if (in_quotes && input[i] == current_quote)
            {
                in_quotes = 0;
                current_quote = '\0';
            }
            else if (!in_quotes)
            {
                in_quotes = 1;
                current_quote = input[i];
            }
            token[token_len++] = input[i];
        }
        else if (ft_isspace(input[i]) && !in_quotes)
        {
            if (token_len > 0)
            {
                token[token_len] = '\0';
                handle_token(token_list, token, &expected);
                token_len = 0;
            }
        }
        else
            token[token_len++] = input[i];

        i++;
    }
    if (token_len > 0)
    {
        token[token_len] = '\0';
        handle_token(token_list, token, &expected);
    }
}
