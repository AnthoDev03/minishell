/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:25:16 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 12:01:05 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../gc/gc.h"
#include "../include/minishell.h"

int		g_sigint_called = 0;

void	process_input_line(char *input, char **copyenv)
{
	t_token	*tokens;
	t_node	*root;

	if (!input)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	add_history(input);
	input = expand_env_variables(input, copyenv);
	tokens = tokenize_with_quotes(input);
	if (tokens != NULL)
	{
		root = parse(tokens);
		execute(root, copyenv);
		free_tree(root);
	}
	free(input);
}

void	loop_minishell(char **copyenv)
{
	char	*input;

	while (1)
	{
		if (!g_sigint_called)
			input = readline("minishell> ");
		else
		{
			input = readline("");
			g_sigint_called = 0;
		}
		if (!input)
		{
			write(STDOUT_FILENO, "", 0);
			exit(0);
		}
		process_input_line(input, copyenv);
		free(input);
	}
}

int	main(int ac, char **ag, char **environ)
{
	char	**copyenv;

	(void)ac;
	(void)ag;
	gc_init();
	copyenv = copieenviron(environ);
	initialize_signal_handlers();
	loop_minishell(copyenv);
	gc_free_all();
	return (0);
}
