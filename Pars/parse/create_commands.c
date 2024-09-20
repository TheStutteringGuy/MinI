/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:20:10 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/09/20 18:10:19 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_pars.h"

t_cmd *create_new_command(t_token *token)
{
    t_cmd *new_cmd;

    new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
    {
        printf("malloc failed");
        exit(1);
    }
    new_cmd->command = ft_strdup(token->value);
    new_cmd->arguments = malloc(sizeof(char *) * 2);
    if (!new_cmd->arguments)
    {
        printf("malloc failed");
        exit(1);
    }
    new_cmd->arguments[0] = NULL;
    new_cmd->redirection = NULL;
    // new_cmd->input_files = NULL;
    // new_cmd->output_files = NULL;
    new_cmd->next = NULL;
    return new_cmd;
}

// Add an argument to the current command
void add_argument_to_command(t_cmd *current_cmd, t_token *token)
{
    int i;
    int j;
    char **new_arguments;

    i = 0;
    while (current_cmd->arguments[i])
        i++;
    new_arguments = malloc(sizeof(char *) * (i + 2));
    if (!new_arguments)
    {
        printf("malloc failed");
        exit(1);
    }
    j = 0;
    while (j < i)
    {
        new_arguments[j] = current_cmd->arguments[j];
        j++;
    }
    new_arguments[i] = ft_strdup(token->value);
    new_arguments[i + 1] = NULL;
    free(current_cmd->arguments);
    current_cmd->arguments = new_arguments;
}

int contains_unexpanded_var(char *filename)
{
    int i = 0;

    while (filename[i])
    {
        // Check if there's an unescaped '$' in the filename
        if (filename[i] == '$' && (i == 0 || filename[i - 1] != '\\'))
            return 1;
        i++;
    }
    return 0;
}

void add_redirection(t_output_input **redirection, char *filename, int heredoc, char *delimiter, int append, int value)
{
    t_output_input *new;
    t_output_input *iterate;
    char *processed_filename;

    if (redirection == NULL)
        exit(1234);
    new = malloc(sizeof(t_output_input));
    if (!new)
        return;
    processed_filename = remove_quotes(filename);
    new->whichis = value;
    new->filename = ft_strdup(processed_filename);
    new->append = append;
    new->heredoc = heredoc;
    if (delimiter)
        new->delimiter = ft_strdup(delimiter);
    else
        new->delimiter = NULL;
    new->next = NULL;
    if (*redirection == NULL)
    {
        *redirection = new;
        return;
    }
    iterate = *redirection;
    while (iterate->next)
        iterate = iterate->next;
    iterate->next = new;
    free(processed_filename);
}


// Handle redirections
void handle_redirections(t_cmd *current_cmd, t_token **current_token)
{
    t_token *token;
    t_token *next_token;

    token = *current_token;
    next_token = token->next;
    if (next_token && (next_token->type == COMMAND || next_token->type == ARGUMENT))
    {
        if (token->type == RED_IN)
            add_redirection(&current_cmd->redirection, next_token->value, 0, NULL, 0, 0);
        else if (token->type == HERDOC)
            add_redirection(&current_cmd->redirection, next_token->value, 1, next_token->value, 0, 0);
        else if (token->type == RED_OUT)
            add_redirection(&current_cmd->redirection, next_token->value, 0, NULL, 0, 1);
        else if (token->type == APPEND)
            add_redirection(&current_cmd->redirection, next_token->value, 0, NULL, 1, 1);

        *current_token = next_token;
    }
    else
        printf("Error: Missing or invalid token after redirection\n");
}

// Main parsing function that iterates over the token list
t_cmd *parse_tokens(t_token *token_list)
{
    t_cmd *cmd_list;
    t_cmd *current_cmd;
    t_token *current_token;
    t_type expected;

    cmd_list = NULL;
    current_cmd = NULL;
    current_token = token_list;
    expected = COMMAND;
    while (current_token)
    {
        process_token(&cmd_list, &current_cmd, &current_token, &expected);
        current_token = current_token->next;
    }
    return cmd_list;
}

t_cmd *create_empty_command(void)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (cmd)
    {
        cmd->command = NULL;
        cmd->arguments = NULL;
        cmd->redirection = NULL;
        // cmd->input_files = NULL;
        // cmd->output_files = NULL;
        cmd->next = NULL;
    }
    else
        printf("Error: Memory allocation failed for new command\n");
    return (cmd);
}
