/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 02:44:33 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/19 14:44:36 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_last_exit_status = 0;

static void	free_littl(char *input, t_token *token_list)
{
	free_tokens(token_list);
	free(input);
}

char	*main_handle_readline(void)
{
	char	*input_;
	char	*input;

	handle_sig();
	input_ = readline("Minishell -> ");
	if (input_ == NULL)
		return (NULL);
	add_history(input_);
	input = trim_spaces(input_);
	free(input_);
	return (input);
}

void	main_2(t_exec *data)
{
	char	*input;
	t_cmd	*cmd_list;
	t_token	*token_list;

	while (TRUE)
	{
		input = main_handle_readline();
		if (input == NULL)
			break ;
		if (!check_syntax_errors_before_tokenize(input))
		{
			free(input);
			continue ;
		}
		if (!validate_input(input))
			continue ;
		token_list = NULL;
		tokenize_input(input, &token_list, data);
		cmd_list = parse_tokens(token_list, data);
		if (!validate_command_list(cmd_list, token_list, input))
			continue ;
		free_littl(input, token_list);
		exec(data, cmd_list);
		free_everything_cmd(&cmd_list);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_exec	data;
	t_cmd	*cmd_list;
	t_token	*token_list;

	initialize_everything(&data, envp, av, ac);
	main_2(&data);
	free_everything_data(&data);
	exit(g_last_exit_status);
}
