/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thestutteringguy <thestutteringguy@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 02:44:33 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/10/17 17:32:25 by thestutteri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_last_exit_status = 0;

void free_red(t_output_input *iterate)
{
	t_output_input *tmp;

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

void free_everything_cmd(t_cmd **input)
{
	t_cmd *iterate;
	t_cmd *tmp;

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

static void free_everything_data(t_exec *data)
{
	clear_list(&data->environ);
	free(data->environ);
	clear_list(&data->export);
	free(data->export);
	rl_clear_history();
}

static void initialize_everything(t_exec *data, char **envp, char **av, int ac)
{
	(void)ac;
	data->environ = NULL;
	data->export = NULL;
	env_list(&data->environ, envp, av);
	update_shlvl(&data->environ);
	copy_environ(&data->export, data->environ);
	remove_list(&data->export, "_");
}

bool validate_input(char *input)
{
	if (input[0] == '\0')
	{
		free(input);
		return (false);
	}
	if (!handle_incorrect_quotes(input))
	{
		free(input);
		return (false);
	}
	return (true);
}

// bool	validate_syntax(t_token *token_list, char *input)
// {
// 	if (check_syntax_errors(token_list))
// 	{
// 		free_tokens(token_list);
// 		free(input);
// 		return (false);
// 	}
// 	return (true);
// }

bool check_syntax_errors_before_tokenize(const char *input)
{
	int i = 0;

	while (input[i] != '\0')
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (input[i] == '|')
		{
			if (i == 0 || input[i + 1] == '|' || input[i + 1] == '\0')
			{
				printf("Syntax error near unexpected token `|'\n");
				return false;
			}
		}
		if (input[i] == '<' || input[i] == '>')
		{
			char redirection = input[i];
			int next_char = i + 1;
			if (input[next_char] == redirection)
				next_char++;
			while (input[next_char] && ft_isspace(input[next_char]))
				next_char++;
			if (input[next_char] == '\0' || input[next_char] == '|' || input[next_char] == '<' || input[next_char] == '>')
			{
				printf("Syntax error near unexpected token `%c'\n", input[i]);
				return false;
			}
		}
		i++;
	}

	return true;
}

bool validate_command_list(t_cmd *cmd_list, t_token *token_list, char *input)
{
	if (cmd_list == NULL)
	{
		free_tokens(token_list);
		free(input);
		return (false);
	}
	return (true);
}

int main(int ac, char **av, char **envp)
{
	char *input_;
	char *input;
	t_exec data;
	t_cmd *cmd_list;
	t_token *token_list;

	initialize_everything(&data, envp, av, ac);
	while (TRUE)
	{
		handle_sig();
		input_ = readline("Minishell -> ");
		if (input_ == NULL)
			break;
		add_history(input_);
		if (!check_syntax_errors_before_tokenize(input_))
		{
			printf("here\n");
			free(input_);
			continue;
		}
		input = trim_spaces(input_);
		free(input_);
		if (!validate_input(input))
			continue;
		// if (input[0] == '\0')
		// {
		// 	free(input);
		// 	continue ;
		// }
		// if (!handle_incorrect_quotes(input))
		// {
		// 	free(input);
		// 	continue ;
		// }
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
		// if (!validate_syntax(token_list, input))
		// 	continue;
		cmd_list = parse_tokens(token_list, &data);
		if (!validate_command_list(cmd_list, token_list, input))
			continue;
		free_tokens(token_list);
		print_commands(cmd_list);
		free(input);
		exec(&data, cmd_list);
		free_everything_cmd(&cmd_list);
	}
	free_everything_data(&data);
	exit(g_last_exit_status);
}
