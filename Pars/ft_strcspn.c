#include "minishell.h"

size_t ft_strcspn(const char *s, const char *reject)
{
    size_t i = 0;

    while (s[i] != '\0')
    {
        const char *r = reject;
        while (*r != '\0')
        {
            if (s[i] == *r++)
                return i;
        }
        i++;
    }

    return i;
}
