#include "mini_pars.h"

void ft_error(char *s1)
{
    int saved_fd;

    saved_fd = dup(STDOUT_FILENO);
    dup2(2, STDOUT_FILENO);
    printf("syntax error near unexpected token `%s`\n", s1);
    dup2(saved_fd, STDERR_FILENO);
}