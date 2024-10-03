/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 02:44:33 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/03 23:19:40 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int last_exit_status = 0;

void free_everything_data(t_exec *data)
{
    clear_list(&data->environ);
    free(data->environ);
    clear_list(&data->export);
    free(data->export);   
}

int main(int ac, char **av, char **envp)
{
    char *input;
    t_cmd *parsed_cmd;
    t_exec data;
    t_cmd *cmd_list;
    t_token *token_list;

    data.environ = NULL;
    data.export = NULL;
    env_list(&data.environ, envp, av);
    update_shlvl(&data.environ);
    copy_environ(&data.export, data.environ);
    remove_list(&data.export, "_");
    while (1)
    {
        handle_sig();
        input = readline("Minishell -> ");
        if (input == NULL)
            break;
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
            printf("\n");
            exec(&data, cmd_list);
            add_history(input);
            free_commands(cmd_list);
            free_tokens(token_list);
            free(input);
        }
    }
    free_everything_data(&data);
    rl_clear_history();
    exit(last_exit_status);
}
