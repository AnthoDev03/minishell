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
#include "../../gc/gc.h"
#include "../../include/minishell.h"

static int	handle_builtin_commands(t_node *node, char **copyenvp)
{
	if (ft_strcmp(node->value, "cd") == 0)
	{
		cd_command(node);
		return (1);
	}
	else if (ft_strcmp(node->value, "echo") == 0)
	{
		echo_command(node);
		return (1);
	}
	else if (ft_strcmp(node->value, "env") == 0)
	{
		env_command(copyenvp);
		return (1);
	}
	else if (ft_strcmp(node->value, "exit") == 0)
	{
		exit_command();
		return (1);
	}
	else if (ft_strcmp(node->value, "pwd") == 0)
	{
		pwd_command();
		return (1);
	}
	else if (ft_strcmp(node->value, "unset") == 0)
	{
		unset_command(node, copyenvp);
		return (1);
	}
	else if (ft_strcmp(node->value, "export") == 0)
	{
		export_command(node, copyenvp);
		return (1);
	}
	return (0);
}

char	**create_args_from_ast(t_node *node)
{
	int		depth;
	t_node	*temp;
	char	**args;
	int		index;

	depth = 0;
	temp = node;
	while (temp)
	{
		depth++;
		if (temp->left)
			temp = temp->left;
		else
			temp = temp->right;
	}
	args = gc_malloc((depth + 1) * sizeof(char *));
	if (!args)
	{
		perror("gc_malloc");
		exit(EXIT_FAILURE);
	}
	index = 0;
	temp = node;
	while (temp)
	{
		args[index] = temp->value;
		index++;
		if (temp->left)
			temp = temp->left;
		else
			temp = temp->right;
	}
	args[index] = NULL;
	return (args);
}

static void	execute_external_command(t_node *node, char **copyenv)
{
	pid_t	pid;
	char	**args;

	args = create_args_from_ast(node);
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
		ft_execvp(args[0], args, copyenv);
		exit(EXIT_FAILURE);
	}
	wait_for_child(pid);
}

void	execute_command(t_node *node, char **copyenv)
{
	if (!handle_builtin_commands(node, copyenv))
		execute_external_command(node, copyenv);
}
