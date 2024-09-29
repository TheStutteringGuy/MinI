#include "../../minishell.h"


char *expand_befor_start(char *input, t_exec *exec)
{
    char *expand_value;

    if (input[0] == '$')
    {
        expand_value = ft_getexport(exec->export, input + 1);
        if (expand_value == NULL)
            return (ft_strdup2(input));
        if (expand_value[0] == '\'')
            exec->flag = 1;
        else
            exec->flag = 0;
        return (ft_strdup2(expand_value));
    }
    return (ft_strdup2(input));
}