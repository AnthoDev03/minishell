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

t_env	*find_variable(char *var_name, t_env *env_list)
{
	int	len;

	len = ft_strlen(var_name);
	while (env_list)
	{
		if (ft_strncmp(env_list->value, var_name, len) == 0
			&& env_list->value[len] == '=')
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	remove_env_var(t_env **head, t_env *target)
{
	t_env	*prev;
	t_env	*curr;

	if (!*head || !target)
		return ;
	if (*head == target)
	{
		*head = (*head)->next;
		free(target->value);
		free(target);
		return ;
	}
	prev = NULL;
	curr = *head;
	while (curr != NULL && curr != target)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL)
		return ;
	prev->next = curr->next;
	free(curr->value);
	free(curr);
}

void	unset_command(t_node *commandnode, t_env **env_list)
{
	char	*var_name;
	t_env	*var_loc;

	if (commandnode->left == NULL || commandnode->left->value == NULL)
	{
		write(2, "unset: missing argument\n", 24);
		return ;
	}
	var_name = commandnode->left->value;
	var_loc = find_variable(var_name, *env_list);
	if (var_loc)
		remove_env_var(env_list, var_loc);
}
