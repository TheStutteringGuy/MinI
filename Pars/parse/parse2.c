#include "../../minishell.h"

void handle_red_in(t_cmd *current_cmd, t_token *next_token, t_exec *exec)
{
    t_redirection_flags flags;
    t_redirection_params params;

    flags = initialize_redirection_flags();
    params = init_redirection_params(next_token->value, NULL, flags);
    add_redirection(&current_cmd->redirection, &params, exec);
}

void create_heredoc(t_cmd *current_cmd, t_token *next_token, t_exec *exec)
{
    t_redirection_flags flags;
    t_redirection_params params;

    flags = initialize_redirection_flags();
    flags.heredoc = 1;
    params = init_redirection_params(next_token->value, next_token->value, flags);
    add_redirection(&current_cmd->redirection, &params, exec);
}

void handle_red_out(t_cmd *current_cmd, t_token *next_token, t_exec *exec)
{
    t_redirection_flags flags;
    t_redirection_params params;

    flags = initialize_redirection_flags();
    flags.value = 1;
    params = init_redirection_params(next_token->value, NULL, flags);
    add_redirection(&current_cmd->redirection, &params, exec);
}

void handle_append(t_cmd *current_cmd, t_token *next_token, t_exec *exec)
{
    t_redirection_flags flags;
    t_redirection_params params;

    flags = initialize_redirection_flags();
    flags.append = 1;
    flags.value = 1;
    params = init_redirection_params(next_token->value, NULL, flags);
    add_redirection(&current_cmd->redirection, &params, exec);
}

void handle_redirections(t_cmd *current_cmd, t_token **current_token, t_exec *exec)
{
    t_token *token;
    t_token *next_token;

    token = *current_token;
    next_token = token->next;

    if (next_token && (next_token->type == COMMAND || next_token->type == ARGUMENT))
    {
        if (token->type == RED_IN)
            handle_red_in(current_cmd, next_token, exec);
        else if (token->type == HERDOC)
            create_heredoc(current_cmd, next_token, exec);
        else if (token->type == RED_OUT)
            handle_red_out(current_cmd, next_token, exec);
        else if (token->type == APPEND)
            handle_append(current_cmd, next_token, exec);
        *current_token = next_token;
    }
    else
        write(2, "Error: Missing or invalid token after redirection\n", 51);
}
