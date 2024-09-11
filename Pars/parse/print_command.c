#include "../mini_pars.h"

// Function to print the command list for debugging
void print_commands(t_cmd *cmd_list)
{
    t_cmd *current;

    current = cmd_list;
    while (current)
    {
        printf("Command: %s\n", current->command);
        printf("Arguments: ");
        for (int i = 1; current->arguments[i]; i++)
            printf("%s ", current->arguments[i]);
        printf("\n");
        // Print input files
        printf("Input files: ");
        t_input_file *input;
        input = current->input_files;
        while (input)
        {
            printf("%s ", input->filename);
            input = input->next;
        }
        printf("\n");
        // Print output files with their redirection types
        printf("Output files: ");
        t_output_file *output;
        output = current->output_files;
        while (output)
        {
            if (output->append)
                printf("%s (Append) ", output->filename);
            else
                printf("%s (Overwrite) ", output->filename);
            output = output->next;
        }
        printf("\n");
        if (current->herdoc)
            printf("Heredoc: %s\n", current->herdoc);
        else
            printf("Heredoc: NULL\n");
        printf("-----\n");
        current = current->next;
    }
}
