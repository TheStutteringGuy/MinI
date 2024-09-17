#include "../mini_pars.h"

int check_syntax_errors(t_token *token_list)
{
    t_token *current;

    current = token_list;
    while (current)
    {
        if (current->type == PIPE || current->type == RED_IN || current->type == RED_OUT ||
            current->type == APPEND || current->type == HERDOC)
        {
            if (current->next == NULL ||
                (current->next->type == PIPE || current->next->type == RED_IN ||
                 current->next->type == RED_OUT || current->next->type == APPEND ||
                 current->next->type == HERDOC))
            {
                printf("Syntax error: unexpected token near `%s`\n", current->value);
                return (1);
            }
        }
        current = current->next;
    }
    return (0);
}

char *trim_spaces(char *str)
{
    while (ft_isspace((unsigned char)*str))
        str++;
    return (str);
}
