#include "../../minishell.h"

char *allocate_new_string(size_t len)
{
    char *new_str;

    new_str = malloc(len + 1);
    if (!new_str)
    {
        write(2, "Error malloc \n", 15);
        exit(1);
    }
    return (new_str);
}

void set_delimiter_flag(t_output_input *new, char *str)
{
    if (str[0] == '\'' || str[0] == '"')
        new->delimiter_expand = 0;
    else
        new->delimiter_expand = 1;
}

void copy_without_quotes(char *new_str, char *str)
{
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] != '\'' && str[i] != '"')
        {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0';
}

char *remove_delimiter_quotes(t_output_input *new, char *str)
{
    size_t len;
    char *new_str;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    new_str = allocate_new_string(len);
    set_delimiter_flag(new, str);
    copy_without_quotes(new_str, str);
    return (new_str);
}
