#include "../../minishell.h"

int handle_invalid_char_after_dollar(char *input, t_norm *norm)
{
	if (!check_for_char(input[norm->i]))
	{
		norm->str[norm->j++] = '$';
		norm->str[norm->j++] = input[norm->i];
		norm->i++;
		return (1);
	}
	return (0);
}