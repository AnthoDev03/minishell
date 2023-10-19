/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:35:31 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:35:34 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../gc/gc.h"
#include "../../include/minishell.h"

int	handle_builtin_commands(t_node *node, char **copyenvp)
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
