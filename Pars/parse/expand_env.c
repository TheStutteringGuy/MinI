#include "../mini_pars.h"

char *expand_env_var(char *token)
{
    char *env_var;
    char *env_value;

    if (token[0] == '$')
    {
        env_var = token + 1;
        env_value = getenv(env_var);
        if (env_value != NULL)
            return (ft_strdup(env_value));
        else
            return (ft_strdup(""));
    }
    return (ft_strdup(token));
}