#include "mini_pars.h"

bool ft_isspace(int c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return (true);
    else
        return (false);
}