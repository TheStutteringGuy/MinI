/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 02:44:33 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/15 01:58:22 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_last_exit_status = 0;

void	free_red(t_output_input *iterate)
{
	t_output_input	*tmp;

	while (iterate)
	{
		tmp = iterate;
		iterate = iterate->next;
		free(tmp->filename);
		free(tmp->delimiter);
		free(tmp->heredoc_file);
		free(tmp);
	}
}

void	free_everything_cmd(t_cmd **input)
{
	t_cmd	*iterate;
	t_cmd	*tmp;

	iterate = *input;
	while (iterate)
	{
		tmp = iterate;
		iterate = iterate->next;
		free(tmp->command);
		free_split(tmp->arguments);
		free_red(tmp->redirection);
		free(tmp);
	}
	*input = NULL;
}

void	free_everything_data(t_exec *data)
{
	clear_list(&data->environ);
	free(data->environ);
	clear_list(&data->export);
	free(data->export);
}

int	main(int ac, char **av, char **envp)
{
	char	*input_;
	char	*input;
	t_exec	data;
	t_cmd	*cmd_list;
	t_token	*token_list;

	// t_cmd	*parsed_cmd;
	(void)ac;
	data.environ = NULL;
	data.export = NULL;
	env_list(&data.environ, envp, av);
	update_shlvl(&data.environ);
	copy_environ(&data.export, data.environ);
	remove_list(&data.export, "_");
	while (TRUE)
	{
		handle_sig();
		input_ = readline("Minishell -> ");
		if (input_ == NULL)
			break ;
		else
		{
			add_history(input_);
			if (input_[0] == '$' && ft_isdigit(input_[1]))
				input = ft_strdup2(input_ + 2);
			input = trim_spaces(input_);
			free(input_);
			if (input[0] == '\0')
			{
				free(input);
				continue ;
			}
			if (!handle_incorrect_quotes(input))
			{
				free(input);
				continue ;
			}
			token_list = NULL;
			tokenize_input(input, &token_list, &data);
			// t_token *iterate;
			// iterate = token_list;
			// while(iterate)
			// {
			//     printf("%s %d\n", iterate->value, iterate->type);
			//     iterate = iterate->next;
			// }
			// continue ;
			if (check_syntax_errors(token_list))
			{
				free_tokens(token_list);
				free(input);
				continue ;
			}
			cmd_list = parse_tokens(token_list, &data);
			if (cmd_list == NULL)
			{
				free_tokens(token_list);
				free(input);
				continue ;
			}
			free_tokens(token_list);
			print_commands(cmd_list);
			printf("\n");
			exec(&data, cmd_list);
			free_everything_cmd(&cmd_list);
			free(input);
		}
	}
	free_everything_data(&data);
	rl_clear_history();
	exit(g_last_exit_status);
}
