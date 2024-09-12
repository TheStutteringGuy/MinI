#include "../mini_pars.h"

// Function to process COMMAND and ARGUMENT tokens
void process_command_or_argument(t_cmd **cmd_list, t_cmd **current_cmd, t_token **current_token, t_type *expected)
{
    t_cmd *new_cmd;

    new_cmd = NULL;
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
    {
        if (*current_cmd)
            add_argument_to_command(*current_cmd, *current_token);
    }
}

// Function to process PIPE, RED_IN, RED_OUT, APPEND, or HERDOC tokens
void process_redirection_or_pipe(t_cmd **cmd_list, t_cmd **current_cmd, t_token **current_token, t_type *expected)
{
    t_cmd *new_cmd;

    new_cmd = NULL;
    if ((*current_token)->type == PIPE)
        *expected = COMMAND;
    else if ((*current_token)->type == RED_IN || (*current_token)->type == RED_OUT ||
             (*current_token)->type == APPEND || (*current_token)->type == HERDOC)
    {
        if (!*current_cmd)
        {
            new_cmd = create_new_command(*current_token);
            if (!*cmd_list)
                *cmd_list = new_cmd;
            else
                (*current_cmd)->next = new_cmd;
            *current_cmd = new_cmd;
        }
        handle_redirections(*current_cmd, current_token);
    }
}

// Main function to process tokens
void process_token(t_cmd **cmd_list, t_cmd **current_cmd, t_token **current_token, t_type *expected)
{
    if ((*current_token)->type == COMMAND || (*current_token)->type == ARGUMENT)
        process_command_or_argument(cmd_list, current_cmd, current_token, expected);
    else if ((*current_token)->type == PIPE || (*current_token)->type == RED_IN ||
             (*current_token)->type == RED_OUT || (*current_token)->type == APPEND ||
             (*current_token)->type == HERDOC)
    {
        process_redirection_or_pipe(cmd_list, current_cmd, current_token, expected);
    }
}