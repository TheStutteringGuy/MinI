/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:30:08 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/03 17:24:09 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static volatile sig_atomic_t signal_received = 0;

// static void sig_handle(int sig)
// {
//     signal_received = 1;
// }

static void here_document_3(t_exec *data, t_output_input *iterate, int fd, char *hered_inp)
{
    char *after_pars;

    if (iterate->delimiter_expand = 1)
    {
        after_pars = expand_herdoc(hered_inp, data);
        write(fd, after_pars, ft_strlen2(after_pars));
        free(after_pars);
    }
    else
        write(fd, hered_inp, ft_strlen2(hered_inp));
    write(fd, "\n", 1);
    free(hered_inp);
}

static void here_document_2(t_exec *data, t_output_input *iterate)
{
    int fd;
    char *hered_inp;

    while (iterate)
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
                here_document_3(data, iterate, fd, hered_inp);
            }
            close(fd);
        }
        iterate = iterate->next;
    }
}

static void here_document(t_exec *data, t_cmd *curr)
{
    t_output_input *iterate;

    while (curr)
    {
        iterate = curr->redirection;
        here_document_2(data, iterate);
        curr = curr->next;
    }
}

static void make_name_2(t_output_input **list)
{
    t_output_input *iterate;
    static int i;
    char *join;
    char *itoa_;

    i = 0;
    iterate = *list;
    while (iterate)
    {
        if (iterate->heredoc == true)
        {
            itoa_ = ft_itoa(i);
            join = ft_strjoin2("/tmp/heredoc", itoa_);
            free(itoa_);
            iterate->heredoc_file = ft_substr(join, 0, ft_strlen2(join));
            free(join);
            i++;
        }
        iterate = iterate->next;
    }
}

static void make_names(t_cmd **input)
{
    t_cmd *curr;
    t_output_input *iterate;
    
    curr = *input;
    while (curr)
    {
        iterate = curr->redirection;
        make_name_2(&iterate);
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

static void child(t_exec *data, t_cmd *input)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
    here_document(data, input);
    exit(0);
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
        child(data, *input);
    signal(SIGINT, SIG_IGN);
    waitpid(id, &status, 0);
    if (!WIFSIGNALED(status))
        last_exit_status = WEXITSTATUS(status);
    else
    {
        last_exit_status = 128 + WTERMSIG(status);
        return (-1);
    }
    return (0);
}
