/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:00:54 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/19 02:19:40 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void copy_environ(t_linked **list, t_linked *environ)
{
  while (environ != NULL)
  {
    create_node(list, ft_substr(environ->key, 0, ft_strlen2(environ->key)), ft_substr(environ->value, 0, ft_strlen2(environ->value)), 1);
    environ = environ->next;
  }
}

void env_list(t_linked **list, char **envp)
{
  int i;
  int j;
  int y;

  i = 0;
  while (envp[i] != NULL)
  {
    y = 0;
    j = 0;
    while (envp[i][j] != '=')
    {
      j++;
    }
    y = j + 1;
    create_node(list, ft_substr(envp[i], 0, j), ft_substr(envp[i], y, ft_strlen2(envp[i])), 1);
    i++;
  }
}

void handle_input_output(t_exec *data, t_cmd *input, int *read_fd, int *write_fd)
{
  t_output_input *iterate;
  char *hered_inp;

  iterate = input->redirection;
  if (iterate != NULL)
  {
    while (iterate)
    {
      if (iterate->whichis == false)
      {
        if (iterate->heredoc == false)
        {
          if (access(iterate->filename, F_OK | R_OK) == 0)
            *read_fd = open(iterate->filename, O_RDONLY);
          else
          {
            printf("%s: %s\n", iterate->filename, strerror(errno));
            last_exit_status = 1;
            *read_fd = -1;
            return ;
          }
        }
        else
        {
          *read_fd = open("HEREDOC", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
          if (*read_fd == -1)
          {
            printf("Poblem in HEREDOC FILE\n");
            exit(1);
          }
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
            write(*read_fd, hered_inp, ft_strlen2(hered_inp));
            write(*read_fd, "\n", 1);
            free(hered_inp);
          }
          close(*read_fd);
          *read_fd = open("HEREDOC", O_CREAT | O_RDWR, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
          unlink("HEREDOC");
        }
      }
      else
      {
        if (iterate->append == true)
          *write_fd = open(iterate->filename, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
        else
          *write_fd = open(iterate->filename, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
      }
      iterate = iterate->next;
    }
    return ;
  }
  *read_fd = 0;
  *write_fd = 1;
}

void handle_simple(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
  int saved_fd;
  size_t len;

  len = ft_strlen2(input->command);
  saved_fd = dup(STDOUT_FILENO);
  if (write_fd != 1)
    dup2(write_fd, STDOUT_FILENO);
  if (len == ft_strlen2("pwd") && ft_strncmp(input->command, "pwd", ft_strlen2("pwd")) == 0)
    pwd_simple(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("env") && ft_strncmp(input->command, "env", ft_strlen2("env")) == 0)
    env_simple(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("echo") && ft_strncmp(input->command, "echo", ft_strlen2("echo")) == 0)
    echo_simple(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("cd") && ft_strncmp(input->command, "cd", ft_strlen2("cd")) == 0)
    cd_simple(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("exit") && ft_strncmp(input->command, "exit", ft_strlen2("exit")) == 0)
    exit_simple(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("export") && ft_strncmp(input->command, "export", ft_strlen2("export")) == 0)
    export_simple(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("unset") && ft_strncmp(input->command, "unset", ft_strlen2("unset")) == 0)
    unset_simple(data, input, read_fd, write_fd);
  else
    execve_handle_simple(data, input, read_fd, write_fd);
  if (write_fd != 1)
    dup2(saved_fd, STDOUT_FILENO);
}

void handle_hard(t_exec *data, t_cmd *input, int read_fd, int write_fd)
{
  int saved_fd;
  size_t len;

  len = ft_strlen2(input->command);
  dup2(read_fd, 0);
  dup2(write_fd, 1);
  if (len == ft_strlen2("pwd") && ft_strncmp(input->command, "pwd", ft_strlen2("pwd")) == 0)
    pwd_hard(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("env") && ft_strncmp(input->command, "env", ft_strlen2("env")) == 0)
    env_hard(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("echo") && ft_strncmp(input->command, "echo", ft_strlen2("echo")) == 0)
    echo_hard(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("cd") && ft_strncmp(input->command, "cd", ft_strlen2("cd")) == 0)
    cd_hard(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("exit") && ft_strncmp(input->command, "exit", ft_strlen2("exit")) == 0)
    exit_hard(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("export") && ft_strncmp(input->command, "export", ft_strlen2("export")) == 0)
    export_hard(data, input, read_fd, write_fd);
  else if (len == ft_strlen2("unset") && ft_strncmp(input->command, "unset", ft_strlen2("unset")) == 0)
    unset_hard(data, input, read_fd, write_fd);
  else
    execve_handle_hard(data, input, read_fd, write_fd);
}

void exec(t_exec *data, t_cmd *input)
{
  int id;
  int write_fd;
  int read_fd;
  int status;

  if (!input->next)
  {
    handle_input_output(data, input, &read_fd, &write_fd);
    if (read_fd == -1)
      return ;
    if (input->command)
      handle_simple(data, input, read_fd, write_fd);
  }
  else
  {
    id = fork();
    if (id == 0)
    {
      signal(SIGINT, SIG_DFL);
      signal(SIGQUIT, SIG_DFL);
      handle_input_output(data, input, &read_fd, &write_fd);
      if (read_fd == -1)
        exit(1);
      handle_hard(data, input, read_fd, write_fd);
      exit(0);
    }
    else
    {
      signal(SIGINT, SIG_IGN);
      waitpid(id, &status, 0);
      last_exit_status = WEXITSTATUS(status);
    }
  }
}
