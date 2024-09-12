#include "../mini_pars.h"

// Function to free tokens array
void free_token(char **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

// Free the memory allocated for tokens
void free_tokens(t_token *token_list)
{
    t_token *current;
    t_token *next;

    current = token_list;
    while (current)
    {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

// Free the memory allocated for input files
void free_input_files(t_input_file *input_list)
{
    t_input_file *current;
    t_input_file *next;

    current = input_list;
    while (current)
    {
        next = current->next;
        free(current->filename);
        free(current);
        current = next;
    }
}

// Free the memory allocated for output files
void free_output_files(t_output_file *output_list)
{
    t_output_file *current;
    t_output_file *next;

    current = output_list;
    while (current)
    {
        next = current->next;
        free(current->filename);
        free(current);
        current = next;
    }
}

void free_commands(t_cmd *cmd_list)
{
    t_cmd *current;
    t_cmd *next;

    current = cmd_list;
    while (current)
    {
        next = current->next;
        free(current->command);
        int i;
        i = 0;
        while (current->arguments[i])
        {
            free(current->arguments[i]);
            i++;
        }
        free(current->arguments);
        free_input_files(current->input_files);
        free_output_files(current->output_files);
        free(current);
        current = next;
    }
}
