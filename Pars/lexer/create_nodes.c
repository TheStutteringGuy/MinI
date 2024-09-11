#include "../minishell.h"

// Function to add a new input file to the linked list
void add_input_file(t_input_file **input_list, char *filename)
{
    t_input_file *new_input;
    t_input_file *current;

    new_input = malloc(sizeof(t_input_file));
    new_input->filename = ft_strdup(filename);
    new_input->next = NULL;
    if (!*input_list)
    {
        *input_list = new_input;
        return;
    }
    current = *input_list;
    while (current->next)
        current = current->next;
    current->next = new_input;
}

// Function to add a new output file to the linked list
void add_output_file(t_output_file **output_list, char *filename, int append)
{
    t_output_file *new_output;
    t_output_file *current;

    new_output = malloc(sizeof(t_output_file));
    new_output->filename = ft_strdup(filename);
    new_output->append = append;
    new_output->next = NULL;
    if (!*output_list)
    {
        *output_list = new_output;
        return;
    }
    current = *output_list;
    while (current->next)
        current = current->next;
    current->next = new_output;
}
