#include "../mini_pars.h"

// Function to print the command list for debugging
void print_commands(t_cmd *cmd_list)
{
    t_cmd *current;

    current = cmd_list;
    if (current == NULL)
    {
        printf("SHIT EMPTY\n");
        exit(1);
    }
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
        printf("redirection: \n");
        while (current->redirection)
        {
            if (current->redirection->whichis == 0)
            {
                t_output_input *input;
                input = current->redirection;
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
            else if (current->redirection->whichis != 0)
            {
                t_output_input *output;
                output = current->redirection;
                printf("%s ", output->filename);
                if (output->append)
                    printf("(Append) \n");
                else
                    printf("(Overwrite) \n");
            }
            printf("NEXT \n");
            current->redirection = current->redirection->next;
        }
        printf("\n");
        printf("-----\n");
        current = current->next;
    }
}
