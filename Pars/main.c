#include "minishell.h"

int main()
{
    char *input;
    while ((input = readline("minishell> ")) != NULL)
    {
        if (*input)
            add_history(input);

        // Expand environment variables in the input
        char *expanded_input = expand_env_variables(input, strlen(input));
        if (!expanded_input)
        {
            free(input);
            continue;
        }

        // Proceed with tokenization and parsing
        t_token *token_list = NULL;
        tokenize_input(expanded_input, &token_list);
        t_cmd *cmd_list = parse_tokens(token_list);
        print_commands(cmd_list);

        // Clean up
        free_tokens(token_list);
        free_commands(cmd_list);
        free(input);
        free(expanded_input);
    }
    return 0;
}
