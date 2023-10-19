/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:38:41 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:38:43 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../gc/gc.h"
#include "../../include/minishell.h"

int	get_environ_length(char **environorig)
{
	int	i;

	i = 0;
	while (environorig[i])
		i++;
	return (i);
}

t_env	*alloc_env_node(void)
{
	t_env	*new_node;

	new_node = (t_env *)gc_malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("Erreur d'allocation mémoire");
		exit(1);
	}
	new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

static t_env	*add_env_node_to_list(t_env *head, char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = alloc_env_node();
	new_node->value = ft_strdup(value);
	if (!new_node->value)
	{
		perror("Erreur d'allocation mémoire");
		exit(1);
	}
	if (!head)
	{
		head = new_node;
		return (head);
	}
	current = head;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (head);
}

t_env	*copy_environ_to_list(char **environorig)
{
	int		i;
	t_env	*head;

	head = NULL;
	i = 0;
	while (environorig[i])
	{
		head = add_env_node_to_list(head, environorig[i]);
		i++;
	}
	return (head);
}
