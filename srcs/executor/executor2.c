/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:35:31 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:35:34 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	init_builtin_commands(char **builtins, void (**funcs)(t_node *))
{
	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "env";
	builtins[3] = "exit";
	builtins[4] = "pwd";
	builtins[5] = "unset";
	builtins[6] = "export";
	funcs[0] = cd_command;
	funcs[1] = echo_command;
	funcs[2] = (void *)env_command;
	funcs[3] = (void *)exit_command;
	funcs[4] = (void *)pwd_command;
	funcs[5] = unset_command;
	funcs[6] = export_command;
}

static int	handle_builtin_commands(t_node *node)
{
	int		i;
	char	*builtins[7];
	void	(*funcs[7])(t_node *);

	init_builtin_commands(builtins, funcs);
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(node->value, builtins[i]) == 0)
		{
			funcs[i](node);
			return (1);
		}
		i++;
	}
	return (0);
}




char **create_args_from_ast(t_node *node) {
    int depth = 0;
    t_node *temp = node;

    // Count the depth of the tree.
    while (temp) {
        depth++;
        temp = temp->left ? temp->left : temp->right;  // Consider right nodes as well
    }

    char **args = malloc((depth + 1) * sizeof(char *));
    if (!args) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int index = 0;

    // Traverse the tree again and store command/arguments in args[].
    temp = node;
    while (temp) {
        args[index++] = temp->value;
        temp = temp->left ? temp->left : temp->right;  // Consider right nodes as well
    }

    args[index] = NULL;

    return args;
}




static void	execute_external_command(t_node *node)
{
	pid_t	pid;
	char **args = create_args_from_ast(node);
	if (node->left)
		args[1] = node->left->value;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		ft_execvp(args[0], args);
		exit(EXIT_FAILURE);
	}
	wait_for_child(pid);
}

void	execute_command(t_node *node)
{
	if (!handle_builtin_commands(node))
		execute_external_command(node);
}
