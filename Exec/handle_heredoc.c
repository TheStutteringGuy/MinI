/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:30:08 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/27 10:55:44 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static volatile sig_atomic_t signal_received = 0;

// static void sig_handle(int sig)
// {
//     signal_received = 1;
// }

static void here_document(t_cmd **input)
{
    t_output_input *iterate;
    t_cmd *curr;
    int i;
    int fd;
    char *hered_inp;
    char *after_pars;

    curr = *input;
    while (curr)
    {
        iterate = curr->redirection;
        while (iterate)
        {
            if (iterate->whichis == false)
            {
                if (iterate->heredoc == true)
                {
                    fd = open(iterate->heredoc_file, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
                    while (TRUE)
                    {
                        hered_inp = readline("> ");
                        if (!hered_inp)
                            break;
                        else if (ft_strlen2(hered_inp) == ft_strlen2(iterate->delimiter) && ft_strncmp(hered_inp, iterate->delimiter, ft_strlen2(iterate->delimiter)) == 0)
                        {
                            free(hered_inp);
                            break;
                        }
                        if (iterate->delimiter_expand = 1)
                        {
                            after_pars = expand_herdoc(hered_inp);
                            write(fd, after_pars, ft_strlen2(after_pars));
                            free(after_pars);
                        }
                        else
                            write(fd, hered_inp, ft_strlen2(hered_inp));
                        write(fd, "\n", 1);
                        free(hered_inp);
                    }
                    close(fd);
                }
            }
            iterate = iterate->next;
        }
        curr = curr->next;
    }
}

static void make_names(t_cmd **input)
{
    t_cmd *curr;
    t_output_input *iterate;
    int i;
    char c;
    char *join;

    i = 0;
    curr = *input;
    while (curr)
    {
        iterate = curr->redirection;
        while (iterate)
        {
            if (iterate->whichis == false)
            {
                if (iterate->heredoc == true)
                {
                    c = i + 48;
                    join = ft_strjoin2("/tmp/heredoc", &c);
                    iterate->heredoc_file = ft_substr(join, 0, ft_strlen2(join));
                    i++;
                    free(join);
                }
            }
            iterate = iterate->next;
        }
        curr = curr->next;
    }
}

static int size(t_cmd *iterate)
{
    int size;
    t_output_input *curr;

    size = 0;
    while (iterate)
    {
        curr = iterate->redirection;
        while (curr)
        {
            if (curr->whichis == false)
            {
                if (curr->heredoc == true)
                    size++;
            }
            curr = curr->next;
        }
        iterate = iterate->next;
    }
    return (size);
}

int handle_heredoc(t_exec *data, t_cmd **input)
{
    pid_t id;
    int status;

    if (size(*input) > 16)
    {
        print_error("maximum here-document count exceeded", NULL, NULL, 0);
        last_exit_status = 2;
        return (-1);
    }
    make_names(input);
    id = fork();
    if (id == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_IGN);
        here_document(input);
        exit(0);
    }
    else
    {
        signal(SIGINT, SIG_IGN);
        waitpid(id, &status, 0);
        if (!WIFSIGNALED(status))
            last_exit_status = WEXITSTATUS(status);
        else
        {
            last_exit_status = 128 + WTERMSIG(status);
            return (-1);
        }
    }
    return (0);
}