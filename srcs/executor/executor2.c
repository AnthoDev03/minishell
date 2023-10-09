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

static void	execute_external_command(t_node *node)
{
	pid_t	pid;
	char	*args[3];

	args[0] = node->value;
	args[1] = NULL;
	args[2] = NULL;
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
