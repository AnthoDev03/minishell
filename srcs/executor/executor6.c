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

int	handle_cd_command(t_node *node)
{
	if (ft_strcmp(node->value, "cd") == 0)
	{
		cd_command(node);
		return (1);
	}
	return (0);
}

int	handle_echo_command(t_node *node)
{
	if (ft_strcmp(node->value, "echo") == 0)
	{
		echo_command(node);
		return (1);
	}
	return (0);
}

int	handle_env_command(t_node *node, t_env *env_list)
{
	if (ft_strcmp(node->value, "env") == 0)
	{
		env_command(env_list);
		return (1);
	}
	return (0);
}

int	handle_exit_command(t_node *node)
{
	if (ft_strcmp(node->value, "exit") == 0)
	{
		exit_command();
		return (1);
	}
	return (0);
}

int	handle_builtin_commands(t_node *node, t_env *env_list)
{
	if (handle_cd_command(node))
		return (1);
	else if (handle_echo_command(node))
		return (1);
	else if (handle_env_command(node, env_list))
		return (1);
	else if (handle_exit_command(node))
		return (1);
	else if (handle_pwd_command(node))
		return (1);
	else if (handle_unset_command(node, env_list))
		return (1);
	else if (handle_export_command(node, env_list))
		return (1);
	return (0);
}
