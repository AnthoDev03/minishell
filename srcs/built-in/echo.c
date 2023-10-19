/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:32:45 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:32:49 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	print_node(t_node *node)
{
	if (node == NULL)
		return ;
	printf("%s", node->value);
	if (node->right != NULL)
		printf(" ");
	print_node(node->right);
}

void	echo_command(t_node *commandnode)
{
	t_node	*argnode;
	int		newline;

	newline = 1;
	argnode = commandnode->left;
	while (argnode != NULL && ft_strcmp(argnode->value, "-n") == 0)
	{
		newline = 0;
		argnode = argnode->right;
	}
	print_node(argnode);
	if (newline)
		printf("\n");
}
