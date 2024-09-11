#include "mini_pars.h"

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    char *dest_start = dest;

    while (n > 0 && *src != '\0')
    {
        *dest++ = *src++;
        n--;
    }

    while (n > 0)
    {
        *dest++ = '\0';
        n--;
    }

    return dest_start;
}
