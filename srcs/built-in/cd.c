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

void	cd_command(t_node *commandNode)
{
	if (commandNode->left == NULL || commandNode->left->value == NULL)
	{
		write(2, "cd: missing argument\n", 20);
		return ;
	}
	if (chdir(commandNode->left->value) != 0)
		perror("cd");
}
