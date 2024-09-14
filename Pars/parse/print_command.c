#include "../mini_pars.h"

// Function to print the command list for debugging
void print_commands(t_cmd *cmd_list)
{
    t_cmd *current;

    current = cmd_list;
    while (current)
    {
        // Print command
        if (current->command)
            printf("Command: %s\n", current->command);
        else
            printf("Command: NULL\n");
        // Print arguments
        printf("Arguments: ");
        for (int i = 0; current->arguments && current->arguments[i]; i++)
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
        // Print details of the input files
        input = current->input_files;
        while (input)
        {
            printf("  - %s: Heredoc = ", input->filename);
            if (input->heredoc)
                printf("true");
            else
                printf("false");
            printf(", Delimiter = ");
            if (input->delimiter)
                printf("%s\n", input->delimiter);
            else
                printf("NULL\n");
            input = input->next;
        }
        // Print output files
        printf("Output files: ");
        t_output_file *output;
        output = current->output_files;
        while (output)
        {
            printf("%s ", output->filename);
            if (output->append)
                printf("(Append) ");
            else
                printf("(Overwrite) ");
            output = output->next;
        }
        printf("\n");
        printf("-----\n");
        current = current->next;
    }
}
