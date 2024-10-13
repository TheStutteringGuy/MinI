#include "../../minishell.h"

void malloc_error()
{
    printf("Error: malloc failed\n");
    exit(1);
}

int check_quotes(char *input, t_exec *exec)
{
    size_t len;

    len = ft_strlen2(input);
    if (exec->quote == 1)
        return (1);
    else if (exec->quote == 2)
        return (2);
    else
        return (0);
}

int count_values(const char *str)
{
    int count = 0;
    int in_value = 0;

    while (*str)
    {
        if (!ft_isspace(*str))
        {
            if (!in_value)
            {
                count++;
                in_value = 1;
            }
        }
        else
        {
            in_value = 0;
        }
        str++;
    }
    return count;
}

char *remove_space(char *str)
{
    int i = 0;
    int j = 0;
    size_t length;

    if (str == NULL)
        return NULL;
    length = ft_strlen2(str);
    char *res = malloc(length + 1);
    if (res == NULL)
        return NULL;
    while (str[i] != '\0')
    {
        if (!ft_isspace(str[i]))
        {
            res[j] = str[i];
            j++;
        }
        i++;
    }
    res[j] = '\0';

    return res;
}

char *handle_incorrect_quotes(char *token)
{

    int i;
    char quots;

    i = 0;
    quots = 0;
    while (token[i])
    {
        if (token[i] == '\'' || token[i] == '"')
        {
            if (quots == 0)
                quots = token[i];
            else if (token[i] == quots)
                quots = 0;
            i++;
        }
        else
            i++;
    }
    if (quots != 0)
    {
        write(2, "Syntax error: unclosed quotesH\n", 32);
        g_last_exit_status = 130;
        return (NULL);
    }
    else
        return (ft_strdup2(token));
}
