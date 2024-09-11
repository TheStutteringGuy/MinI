#include "mini_pars.h"

char *ft_strcpy(char *dest, const char *src)
{
    char *dest_start = dest;

    while ((*dest++ = *src++))
        ;

    return dest_start;
}
