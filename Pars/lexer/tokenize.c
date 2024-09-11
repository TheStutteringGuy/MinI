#include "../minishell.h"

// Function to create a new token
t_token *create_token(t_type type, char *value)
{
    t_token *new_token;

    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->type = type;
    new_token->value = ft_strdup(value);
    new_token->next = NULL;
    return new_token;
}

// Function to add a token to the end of the list
void add_token(t_token **head, t_token *new_token)
{
    if (!*head)
    {
        *head = new_token;
        return;
    }
    t_token *current = *head;
    while (current->next)
        current = current->next;
    current->next = new_token;
}

// Function to classify tokens and return the appropriate type
t_type classify_token(char *token, t_type expected)
{
    if (ft_strcmp(token, "|") == 0)
        return PIPE;
    else if (ft_strcmp(token, "<") == 0)
        return RED_IN;
    else if (ft_strcmp(token, ">") == 0)
        return RED_OUT;
    else if (ft_strcmp(token, "<<") == 0)
        return HERDOC;
    else if (ft_strcmp(token, ">>") == 0)
        return APPEND;
    else
        return expected;
}

// Function to handle the token by classifying and adding it to the list
void handle_token(t_token **token_list, char *token, t_type *expected)
{
    t_type type;

    type = classify_token(token, *expected);
    add_token(token_list, create_token(type, token));
    if (type == PIPE)
        *expected = COMMAND;
    else if (type == COMMAND)
        *expected = ARGUMENT;
}

// Main function to tokenize input
void tokenize_input(char *input, t_token **token_list)
{
    char **tokens;
    t_type expected;
    int i;

    tokens = ft_split(input, ' ');
    expected = COMMAND;
    i = 0;
    while (tokens[i])
    {
        handle_token(token_list, tokens[i], &expected);
        i++;
    }
    free_token(tokens);
}
