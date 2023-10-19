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
#include "../../gc/gc.h"
#include "../../include/minishell.h"

char	**find_variable(char *var_name, char **copyenv)
{
	int	len;

	len = ft_strlen(var_name);
	while (*copyenv)
	{
		if (ft_strncmp(*copyenv, var_name, len) == 0 && (*copyenv)[len] == '=')
			return (copyenv);
		copyenv++;
	}
	return (NULL);
}

void	shift_env_vars_left(char **start)
{
	char	**dest;

	dest = start;
	while (*dest)
	{
		*dest = *(dest + 1);
		dest++;
	}
}

void	unset_command(t_node *commandNode, char **copyenv)
{
	char	*var_name;
	char	**var_loc;

	if (commandNode->left == NULL || commandNode->left->value == NULL)
	{
		write(2, "unset: missing argument\n", 24);
		return ;
	}
	var_name = commandNode->left->value;
	var_loc = find_variable(var_name, copyenv);
	if (var_loc)
		shift_env_vars_left(var_loc);
}
