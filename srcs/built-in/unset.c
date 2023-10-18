/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:34:32 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:34:35 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
#include "../../gc/gc.h"

char **find_variable(char *var_name, char **copyenv)
{
	char **env;
	int len;

	env = copyenv; // Utilisez copyenv au lieu de environ
	len = ft_strlen(var_name);
	while (*env)
	{
		if (ft_strncmp(*env, var_name, len) == 0 && (*env)[len] == '=')
			return (env);
		env++;
	}
	return (NULL);
}

void shift_env_vars_left(char **start)
{
	char **dest;

	dest = start;
	while (*dest)
	{
		*dest = *(dest + 1);
		dest++;
	}
}

void unset_command(t_node *commandNode, char **copyenv) // Ajoutez l'argument copyenv
{
	char *var_name;
	char **var_loc;

	if (commandNode->left == NULL || commandNode->left->value == NULL)
	{
		write(2, "unset: missing argument\n", 24);
		return;
	}
	var_name = commandNode->left->value;
	var_loc = find_variable(var_name, copyenv); // Passez copyenv comme argument
	if (var_loc)
		shift_env_vars_left(var_loc);
}

