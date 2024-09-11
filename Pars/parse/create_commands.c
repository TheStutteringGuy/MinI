#include "../minishell.h"

// Create a new command
t_cmd *create_new_command(t_token *token)
{
    t_cmd *new_cmd;

    new_cmd = malloc(sizeof(t_cmd));
    new_cmd->command = ft_strdup(token->value);
    new_cmd->arguments = malloc(sizeof(char *) * 2);
    new_cmd->arguments[0] = ft_strdup(token->value);
    new_cmd->arguments[1] = NULL;
    new_cmd->input_files = NULL;
    new_cmd->output_files = NULL;
    new_cmd->herdoc = NULL;
    new_cmd->next = NULL;
    return (new_cmd);
}

// Add an argument to the current command
void add_argument_to_command(t_cmd *current_cmd, t_token *token)
{
    int i;
    int j;
    char **new_arguments;

    i = 0;
    while (current_cmd->arguments[i])
        i++;
    new_arguments = malloc(sizeof(char *) * (i + 2));
    if (!new_arguments)
    {
        printf("malloc failed");
        exit(1);
    }
    j = 0;
    while (j < i)
    {
        new_arguments[j] = current_cmd->arguments[j];
        j++;
    }
    new_arguments[i] = ft_strdup(token->value);
    new_arguments[i + 1] = NULL;
    free(current_cmd->arguments);
    current_cmd->arguments = new_arguments;
}

// Handle redirections
void handle_redirections(t_cmd *current_cmd, t_token **current_token)
{
    t_token *token;
    t_token *next_token;

    token = *current_token;
    next_token = token->next;
    if (next_token && (next_token->type == COMMAND || next_token->type == ARGUMENT))
    {
        if (token->type == RED_IN)
            add_input_file(&current_cmd->input_files, next_token->value);
        else if (token->type == RED_OUT)
            add_output_file(&current_cmd->output_files, next_token->value, 0);
        else if (token->type == APPEND)
            add_output_file(&current_cmd->output_files, next_token->value, 1);
        else if (token->type == HERDOC)
            current_cmd->herdoc = ft_strdup(next_token->value);
        *current_token = next_token;
    }
}

void process_token(t_cmd **cmd_list, t_cmd **current_cmd, t_token **current_token, t_type *expected)
{
    t_cmd *new_cmd;
    
    new_cmd = NULL;
    if ((*current_token)->type == COMMAND || (*current_token)->type == ARGUMENT)
    {
        if (*expected == COMMAND)
        {
            new_cmd = create_new_command(*current_token);
            if (!*cmd_list)
                *cmd_list = new_cmd;
            else
                (*current_cmd)->next = new_cmd;
            *current_cmd = new_cmd;
            *expected = ARGUMENT;
        }
        else if (*expected == ARGUMENT)
            add_argument_to_command(*current_cmd, *current_token);
    }
    else if ((*current_token)->type == PIPE)
        *expected = COMMAND;
    else if ((*current_token)->type == RED_IN || (*current_token)->type == RED_OUT ||
             (*current_token)->type == APPEND || (*current_token)->type == HERDOC)
    {
        handle_redirections(*current_cmd, current_token);
    }
}

// Main parsing function that iterates over the token list
t_cmd *parse_tokens(t_token *token_list)
{
    t_cmd *cmd_list;
    t_cmd *current_cmd;
    t_token *current_token;
    t_type expected;

    cmd_list = NULL;
    current_cmd = NULL;
    current_token = token_list;
    expected = COMMAND;
    while (current_token)
    {
        process_token(&cmd_list, &current_cmd, &current_token, &expected);
        current_token = current_token->next;
    }
    return cmd_list;
}
