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
#include "../include/minishell.h"

void print_lexer(t_token *tokens) {
    if (!tokens) return;

    printf("Tokens:\n");
    while (tokens->type != TOKEN_EOF) {
        printf("Type: ");
        switch (tokens->type) {
            case TOKEN_COMMAND: printf("COMMAND"); break;
            case TOKEN_ARGUMENT: printf("ARGUMENT"); break;
            case TOKEN_PIPE: printf("PIPE"); break;
            case TOKEN_REDIRECT_IN: printf("REDIRECT_IN"); break;
            case TOKEN_REDIRECT_OUT: printf("REDIRECT_OUT"); break;
            case TOKEN_REDIRECT_IN_APPEND: printf("REDIRECT_IN_APPEND"); break;
            case TOKEN_REDIRECT_OUT_APPEND: printf("REDIRECT_OUT_APPEND"); break;
            default: printf("UNKNOWN");
        }
        if (tokens->value)
            printf(", Value: %s\n", tokens->value);
        else
            printf("\n");
        tokens++;
    }
}

void print_parser_helper(t_node *node, int level) {
    if (!node) return;

    for (int i = 0; i < level; i++) printf("  "); // Indentation

    switch (node->type) {
        case NODE_COMMAND: printf("COMMAND: %s\n", node->value); break;
        case NODE_ARGUMENT: printf("ARGUMENT: %s\n", node->value); break;
        case NODE_PIPE: printf("PIPE\n"); break;
        case NODE_REDIRECT_IN: printf("REDIRECT_IN: %s\n", node->value); break;
        case NODE_REDIRECT_OUT: printf("REDIRECT_OUT: %s\n", node->value); break;
        case NODE_REDIRECT_IN_APPEND: printf("REDIRECT_IN_APPEND: %s\n", node->value); break;
        case NODE_REDIRECT_OUT_APPEND: printf("REDIRECT_OUT_APPEND: %s\n", node->value); break;
        default: printf("UNKNOWN\n");
    }

    print_parser_helper(node->left, level + 1);
    print_parser_helper(node->right, level + 1);
}

void print_parser(t_node *root) {
    printf("Abstract Syntax Tree (AST):\n");
    print_parser_helper(root, 0);
}
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

void	initialize_signal_handlers(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	process_input_line(char *input)
{
	t_token	*tokens;
	t_node	*root;

	if (!input)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	add_history(input);
	input = expand_env_variables(input);
	tokens = tokenize_with_quotes(input);
//  print_lexer(tokens);
	if (tokens != NULL)
	{
		root = parse(tokens);
  //  print_parser(root);
		execute(root);
		free_tree(root);
	}
	free(input);
}

int	main(void)
{
	char	*input;

	initialize_signal_handlers();
	input = readline("minishell> ");
	while (input)
	{
		process_input_line(input);
		input = readline("minishell> ");
	}
	return (0);
}
