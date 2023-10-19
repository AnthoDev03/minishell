/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:34:06 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:34:11 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../gc/gc.h"
#include "../../include/minishell.h"

char	*create_new_entry(char *key, char *value)
{
	int		len;
	char	*new_entry;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	new_entry = gc_malloc(len);
	if (!new_entry)
	{
		write(2, "Memory allocation failed\n", 23);
		return (NULL);
	}
	ft_strcpy(new_entry, key);
	ft_strcat(new_entry, "=");
	ft_strcat(new_entry, value);
	return (new_entry);
}

void	replace_existing_var(t_env *node, char *key, char *value)
{
	char	*new_entry;

	new_entry = create_new_entry(key, value);
	if (new_entry)
	{
		free(node->value);
		node->value = new_entry;
	}
}

t_env	*is_key_present(t_env *env_list, char *key, int len)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->value, key, len) == 0
			&& env_list->value[len] == '=')
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	add_new_env_var(t_env **env_list, char *key, char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = gc_malloc(sizeof(t_env));
	if (!new_node)
	{
		write(2, "Memory allocation failed\n", 24);
		return ;
	}
	new_node->value = create_new_entry(key, value);
	new_node->next = NULL;
	if (!*env_list)
		*env_list = new_node;
	else
	{
		current = *env_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}
