/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 02:44:33 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/29 21:11:15 by thestutteri      ###   ########.fr       */
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
    update_shlvl(&data.environ);
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
            input = expand_befor_start(input, &data);
            printf("input ---> %s\n", input);
            tokenize_input(input, &token_list);
            if (check_syntax_errors(token_list))
            {
                free_tokens(token_list);
                free(input);
                continue;
            }
            cmd_list = parse_tokens(token_list, &data);
            if (cmd_list == NULL)
            {
                free_tokens(token_list);
                free(input);
                continue;
            }
            print_commands(cmd_list);
            printf("\n\n");
            exec(&data, cmd_list);
            printf("\n\n");
            add_history(input);
            free_commands(cmd_list);
            free_tokens(token_list);
            free(input);
        }
    }
    return 0;
}
