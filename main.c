/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 02:44:33 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/23 16:41:41 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_everything()
{
}

void input_null(char *input)
{
    printf("exit\n"); // Ctrl+d Pressed
    free(input);
    exit(0);
}
int last_exit_status = 0;

int main(int ac, char **av, char **envp)
{
    char *input;
    t_cmd *parsed_cmd;
    t_exec data;
    t_cmd *cmd_list;
    t_token *token_list;

    (void)ac;
    (void)av;

    // Initialize linked lists to NULL
    data.environ = NULL;
    data.export = NULL;

    // Create and populate environment variable list
    env_list(&data.environ, envp);

    // Create a copy of the environment variable list for exports
    copy_environ(&data.export, data.environ);

    while (1)
    {
        handle_sig();
        input = readline("Minishell -> ");
        if (input == NULL)
            input_null(input);
        else
        {
            input = trim_spaces(input);
            if (input[0] == '\0')
            {
                free(input);
                continue;
            }
            if (!handle_incorrect_quotes(input))
            {
                free(input);
                continue;
            }
            token_list = NULL;
            tokenize_input(input, &token_list);
            if (check_syntax_errors(token_list))
            {
                free_tokens(token_list);
                free(input);
                continue;
            }

            // Pass data.environ to parse_tokens function
            cmd_list = parse_tokens(token_list, data.environ);
            if (cmd_list == NULL)
            {
                free_tokens(token_list);
                free(input);
                continue;
            }
            print_commands(cmd_list);
            printf("\n\n");

            // Execute the parsed command list
            exec(&data, cmd_list);

            printf("\n\n");

            add_history(input);

            // Free memory associated with commands and tokens
            free_commands(cmd_list);
            free_tokens(token_list);
            free(input); // Free input as well
        }
    }

    // Free all memory and exit gracefully
    free_environment(data.environ);
    free_environment(data.export);

    return 0;
}
