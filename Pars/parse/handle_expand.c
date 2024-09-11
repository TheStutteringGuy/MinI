#include "../minishell.h"

char *expand_variable(const char *var_name)
{
    char *expanded = getenv(var_name);
    if (expanded)
        return ft_strdup(expanded);
    else
        return ft_strdup("");
}

char *expand_env_variables(const char *str, size_t length)
{
    char *result = malloc(length + 1);
    if (!result)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    ft_strlcpy(result, str, length + 1);

    // Check if the string is enclosed in single quotes
    if (str[0] == '\'' && str[length - 1] == '\'')
    {
        // Remove single quotes and return without expansion
        result[length - 1] = '\0';
        ft_memmove(result, result + 1, length - 1);
        return result;
    }

    // Expand variables in double quotes
    if (str[0] == '"' && str[length - 1] == '"')
    {
        result[length - 1] = '\0';
        ft_memmove(result, result + 1, length - 1);
    }

    size_t i = 0;
    while (result[i] != '\0')
    {
        if (result[i] == '$')
        {
            char *var_start = &result[i + 1];

            // Check if the variable starts with an invalid character
            if (isdigit(var_start[0]) || !isalpha(var_start[0]))
            {
                // Skip the `$` and the first invalid character
                ft_memmove(result + i, result + i + 2, ft_strlen(result) - i - 1);
                continue;
            }

            size_t var_length = ft_strcspn(var_start, " \"$'");

            char var_name[var_length + 1];
            ft_strncpy(var_name, var_start, var_length);
            var_name[var_length] = '\0';

            char *expanded_var = expand_variable(var_name);
            if (expanded_var)
            {
                size_t expanded_length = ft_strlen(expanded_var);
                size_t new_length = ft_strlen(result) + expanded_length - var_length;
                char *new_result = malloc(new_length + 1);
                if (!new_result)
                {
                    printf("Memory allocation failed\n");
                    exit(1);
                }

                // Copy up to the variable, insert expanded value, and append the rest
                ft_strlcpy(new_result, result, i);
                ft_strcpy(new_result + i, expanded_var);
                ft_strcpy(new_result + i + expanded_length, var_start + var_length);

                free(result);
                result = new_result;
                i += expanded_length - 1;
                free(expanded_var);
            }
        }
        else
        {
            i++;
        }
    }

    return result;
}
