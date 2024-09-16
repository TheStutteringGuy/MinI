/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 02:44:33 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/16 20:59:25 by thestutteri      ###   ########.fr       */
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

    (void)envp;
    (void)ac;
    (void)av;
    data.environ = malloc(sizeof(t_linked));
    if (!data.environ)
    {
        printf("data.environ failed\n");
        exit(1);
    }
    data.export = malloc(sizeof(t_linked));
    if (!data.export)
    {
        free(data.environ);
        printf("data.export failed\n");
        exit(1);
    }
    data.environ = NULL;
    env_list(&data.environ, envp);
    data.export = NULL;
    copy_environ(&data.export, data.environ);
    while (1)
    {
        handle_sig();
        input = readline("Minishell -> ");
        if (input == NULL)
            input_null(input);
        else if (input[0] == '\0' || ft_isspace(*input))
            free(input);
        else
        {
            if (!handle_incorrect_quotes(input))
            {
                free(input);
                continue;
            }
            add_history(input);
            t_token *token_list = NULL;
            tokenize_input(input, &token_list);
            if (check_syntax_errors(token_list))
            {
                free_tokens(token_list);
                free(input);
                continue;
            }
            t_cmd *cmd_list = parse_tokens(token_list);
            print_commands(cmd_list);
            printf("\n\n");
            exec(&data, cmd_list);
            printf("\n\n");
            // free_tokens(token_list);
            // free_commands(cmd_list);
            free_everything();
        }
    }
    return 0;
}
