#include "../include/minishell.h"
#include <stdio.h>


void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nminishell> ", 12);
	rl_on_new_line_with_prompt();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_node	*root;

	struct sigaction sa_int, sa_quit;
	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	while ((input = readline("minishell> ")))
	{
		if (!input)
		{
			write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}
		add_history(input);
		input = expand_env_variables(input);
		tokens = tokenize_with_quotes(input);
		if (tokens != NULL)
		{
			root = parse(tokens);
			execute(root);
			free_tree(root);
		}
		free(input);
	}
	return (0);
}
