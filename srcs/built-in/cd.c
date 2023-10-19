/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:32:24 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:32:30 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	cd_command(t_node *commandnode)
{
	char	*path;

	if (commandnode->left == NULL || commandnode->left->value == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			write(2, "cd: HOME not set\n", 17);
			return ;
		}
	}
	else
		path = commandnode->left->value;
	if (chdir(path) != 0)
		perror("cd");
}
