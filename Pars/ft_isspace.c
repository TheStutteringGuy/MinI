#include "mini_pars.h"

bool ft_isspace(int c)
{
    if (c == ' ' || (9 <= c && c >= 13))
        return (true);
    else
        return (false);
}