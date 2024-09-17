#include "../mini_pars.h"

char *expand_env_var(char *token)
{
    char *env_var;
    char *env_value;

    if (token[0] == '$')
    {
        if (ft_strcmp(token, "$?") == 0)
            return (ft_itoa(last_exit_status));
        if (ft_isdigit(token[1]))
            return (ft_strdup(token + 2));
        else
            env_var = token + 1;
        env_value = getenv(env_var);
        if (env_value != NULL)
            return (ft_strdup(env_value));
        else
        {
            printf("Invalid env \n");
            return (ft_strdup(""));
        }
    }
    return (ft_strdup(token));
}