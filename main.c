/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 02:44:33 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/12 03:24:33 by ahmed            ###   ########.fr       */
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
        else
        {
            add_history(input);
            t_token *token_list = NULL;
            tokenize_input(input, &token_list);
            t_cmd *cmd_list = parse_tokens(token_list);
            print_commands(cmd_list);
            free_tokens(token_list);
            free_commands(cmd_list);
        }
        free_everything();
    }
    return 0;
}
