/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:00:54 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/09/15 02:37:48 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    copy_environ(t_linked **list, t_linked *environ)
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

int  handle_input(t_exec *data, t_cmd *input)
{
  t_input_file *iterate;
  int fd;

  iterate = input->input_files;
  if (iterate != NULL)
  {
    while (iterate)
    {
      if (iterate->heredoc == false)
      {
        if (access(iterate->filename, F_OK | R_OK) == 0)
        {
          fd = open(iterate->filename, O_RDONLY);
          return(fd);
        }
        else
        {
          printf("%s: %s\n", iterate->filename, strerror(errno));
          exit(1);
        }
      }
      iterate = iterate->next;
     }
  }
  return (0);
}

int  handle_output(t_exec *data, t_cmd *input)
{
  t_output_file *iterate;
  int fd;
  
  iterate = input->output_files;
  if (iterate != NULL)
  {
    while (iterate)
    {
      if (iterate->append == true)
        fd = open(iterate->filename, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
      else
        fd = open(iterate->filename, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
      iterate = iterate->next;
    }
    return (fd);
  }
  return (1);
}

void exec(t_exec *data, t_cmd *input)
{
  size_t len;
  int read_fd;
  int write_fd;

  read_fd = 0;
  write_fd = 1;
  if (!input->next)
  {
    read_fd = handle_input(data, input);
    write_fd = handle_output(data, input);
    if (input->command)
    {
        len = ft_strlen2(input->command);
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
    }
  }
  else
    printf("HARD\n");
}
