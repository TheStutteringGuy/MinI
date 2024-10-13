/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:27:09 by aahlaqqa          #+#    #+#             */
/*   Updated: 2024/10/13 14:17:41 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redirection_params	init_redirection_params(char *filename, char *delimiter,
		t_redirection_flags flags)
{
	t_redirection_params	params;

	params.filename = filename;
	params.delimiter = delimiter;
	params.flags = flags;
	return (params);
}

void	process_filename(t_output_input *new, char *filename, t_exec *exec)
{
	char	*processed_filename;
	t_norm	norm;

	norm.i = 0;
	norm.j = 0;
	norm.str = NULL;
	norm.expanded = NULL;
	norm.count = 0;
	norm.str1 = NULL;
	processed_filename = remove_quotes(filename, exec, &norm);
	if (processed_filename == NULL)
	{
		new->ambigious = 1;
		new->filename = ft_strdup2(filename);
	}
	else
	{
		new->ambigious = 0;
		new->filename = ft_strdup2(processed_filename);
		free(processed_filename);
	}
}


void	process_delimiter(t_output_input *new, char *delimiter, t_exec *exec)
{
	char	*processed_delimiter;

	if (delimiter != NULL)
	{
		exec->eof = 1;
		processed_delimiter = remove_delimiter_quotes(new, delimiter);
		new->delimiter = ft_strdup2(processed_delimiter);
		free(processed_delimiter);
	}
	else
	{
		new->delimiter = NULL;
	}
}

void	add_redirection(t_output_input **redirection,
		t_redirection_params *params, t_exec *exec)
{
	t_output_input	*new;
	t_output_input	*iterate;

	new = malloc(sizeof(t_output_input));
	if (!new)
		return ;
	new->whichis = params->flags.value;
	process_filename(new, params->filename, exec);
	new->append = params->flags.append;
	new->heredoc = params->flags.heredoc;
	process_delimiter(new, params->delimiter, exec);
	new->next = NULL;
	if (*redirection == NULL)
	{
		*redirection = new;
		return ;
	}
	iterate = *redirection;
	while (iterate->next)
		iterate = iterate->next;
	iterate->next = new;
}

t_redirection_flags	initialize_redirection_flags(void)
{
	t_redirection_flags	flags;

	flags.heredoc = 0;
	flags.append = 0;
	flags.value = 0;
	return (flags);
}
