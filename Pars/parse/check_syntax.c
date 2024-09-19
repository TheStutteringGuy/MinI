#include "../mini_pars.h"

int check_syntax_errors(t_token *token_list)
{
    t_token *current;
    t_token *after_red;

    current = token_list;
    while (current)
    {
        if (current->type == PIPE && current->next == NULL)
        {
            printf("syntax error near unexpected token  `%s`\n", current->value);
            last_exit_status = 2;
            return (1);
        }
        else if (current->type == PIPE && current->next->type != COMMAND && current->next->type != ARGUMENT)
        {
            after_red = current->next->next;
            if (after_red == NULL || after_red->type == RED_IN || after_red->type == RED_OUT || after_red->type == HERDOC || after_red->type == APPEND)
            {
                printf("syntax error near unexpected token `%s`\n", current->value);
                last_exit_status = 2;
                return (1);
            }
        }
        else if (current->type == PIPE || current->type == RED_IN || current->type == RED_OUT ||
                 current->type == APPEND || current->type == HERDOC)
        {
            if (current->next == NULL ||
                (current->next->type == PIPE || current->next->type == RED_IN ||
                 current->next->type == RED_OUT || current->next->type == APPEND ||
                 current->next->type == HERDOC))
            {
                printf("syntax error near unexpected token  `%s`\n", current->value);
                last_exit_status = 2;
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
