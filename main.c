/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 02:44:33 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/27 11:54:32 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int last_exit_status = 0;

void free_everything()
{
}

void input_null(char *input)
{
    printf("exit\n"); // Ctrl+d Pressed
    free(input);
    exit(0);
}
static size_t key_return(char *key, char *key2)
{
    size_t len;

    len = ft_strlen2(key);
    if (len < ft_strlen2(key2))
        len = ft_strlen2(key2);
    return (len);
}

void    update_shlvl(t_linked **environ)
{
    t_linked *iterate;
    size_t len;
    int new_value;
    char *new_shlvl;

    iterate = *environ;
    while (iterate)
    {
        len = key_return(iterate->key, "SHLVL");
        if (ft_strncmp(iterate->key, "SHLVL", len) == 0)
        {
            new_shlvl = ft_atoui(iterate->value) + 1;
            if (new_shlvl < 0)
                new_shlvl = 0;
            else if (new_shlvl >= 1000)
            {
                printf("warning: shell level (%d) too high, resetting to 1\n", (int)ft_atoui(new_shlvl));
                new_shlvl = 1;
            }
            free(iterate->value);
            new_value = ft_itoa(new_shlvl);
            iterate->value = ft_substr(new_value, 0, ft_strlen2(new_value));
        }
        iterate = iterate->next;
    } 
}

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
