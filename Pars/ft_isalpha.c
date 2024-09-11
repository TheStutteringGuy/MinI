#include "minishell.h"

int ft_isalpha(int c)
{
    // Checks if c is between 'A' and 'Z' or between 'a' and 'z'
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
