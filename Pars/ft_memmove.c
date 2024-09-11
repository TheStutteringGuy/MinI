#include "minishell.h"

void *ft_memmove(void *dest, const void *src, size_t n)
{
    unsigned char *d;
    const unsigned char *s;

    d = dest;
    s = src;
    if (d < s)
    {
        size_t i;
        i = 0;
        while (i < n)
        {
            d[i] = s[i];
            i++;
        }
    }
    else
    {
        size_t i;
        i = n;
        while (i > 0)
        {
            i--;
            d[i] = s[i];
        }
    }

    return dest;
}
