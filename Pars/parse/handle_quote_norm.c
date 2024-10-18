#include "../../minishell.h"

int is_empty_quotes_sequence(char *input, t_norm *norm, t_exec *exec)
{
    if (((input[norm->i] == '\'' && input[norm->i + 1] == '\'') ||
         (input[norm->i] == '"' && input[norm->i + 1] == '"')) &&
        exec->is_in == 0)
    {
        return (1);
    }
    return (0);
}

int is_dollar_followed_by_quote(char *input, t_norm *norm, t_exec *exec)
{
    if (input[norm->i] == '$' &&
        (input[norm->i + 1] == '"' || input[norm->i + 1] == '\'') &&
        exec->quote == 0)
    {
        return (1);
    }
    return (0);
}

int is_dollar_followed_by_quote_with_exec_quote_two(char *input, t_norm *norm, t_exec *exec)
{
    if (input[norm->i] == '$' &&
        (input[norm->i + 1] == '"' || input[norm->i + 1] == '\'') &&
        exec->quote == 2)
    {
        return (1);
    }
    return (0);
}