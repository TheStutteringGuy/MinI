#include "../mini_pars.h"

// Function to handle double quotes
char *remove_quotes(char *token)
{
    size_t len;
    char *new_token;
    int i;
    int j;
    char current_quote;

    len = ft_strlen(token);
    if (len < 2)
        return (ft_strdup(token));

    new_token = malloc(len + 1);
    if (!new_token)
    {
        printf("Error: malloc failed\n");
        exit(1);
    }
    i = 0;
    j = 0;
    current_quote = '\0';
    while (i < len)
    {
        if ((token[i] == '"' || token[i] == '\'') && current_quote == '\0')
        {
            current_quote = token[i];
            i++;
        }
        else if (token[i] == current_quote)
        {
            current_quote = '\0';
            i++;
        }
        else
            new_token[j++] = token[i++];
    }
    new_token[j] = '\0';
    return (new_token);
}

char *handle_incorrect_quotes(char *token)
{
    size_t len;
    int single_quotes;
    int double_quotes;
    size_t i;

    len = ft_strlen(token);
    single_quotes = 0;
    double_quotes = 0;
    i = 0;
    while (i < len)
    {
        if (token[i] == '\'')
            single_quotes++;
        else if (token[i] == '"')
            double_quotes++;
        i++;
    }
    if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
    {
        printf("Syntax error: unclosed quotes\n");
        return NULL;
    }
    return (ft_strdup(token));
}
