#include "../../minishell.h"

void handle_dollar_end_case(char *input, t_helpe *helpe, t_token **token_list, t_exec *exec)
{
    int k = 0;

    if (helpe->res != NULL)
    {
        while (helpe->res[k] != '\0')
            helpe->token[helpe->token_len++] = helpe->res[k++];
    }
    helpe->token[helpe->token_len++] = '$';
    helpe->token[helpe->token_len] = '\0';
    handle_token(token_list, helpe->token, helpe, exec);
    helpe->token_len = 0;
    helpe->i++;
}

void handle_non_empty_result(t_helpe *helpe, t_token **token_list, t_exec *exec, int is_dollar_at_end)
{
    if (is_dollar_at_end)
    {
        handle_dollar_at_end(helpe, token_list, exec);
    }
    else
    {
        handle_result_input(helpe, token_list, exec);
    }
}
