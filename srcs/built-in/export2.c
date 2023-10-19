/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:33:47 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:33:51 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../gc/gc.h"
#include "../../include/minishell.h"

void	handle_var_set(t_env **env_list, char *key, char *value)
{
	int		len;
	t_env	*existing_var;

	len = ft_strlen(key);
	existing_var = is_key_present(*env_list, key, len);
	if (existing_var)
		replace_existing_var(existing_var, key, value);
	else
		add_new_env_var(env_list, key, value);
}

void	set_env_var(t_node *commandNode, t_env **env_list)
{
	char	*key;
	char	*equal_sign;
	char	*value;

	key = commandNode->left->value;
	equal_sign = ft_strchr(key, '=');
	if (!equal_sign || equal_sign == key)
	{
		printf("Malformed input: %s. Expected format: KEY=VALUE\n", key);
		return ;
	}
	*equal_sign = '\0';
	value = equal_sign + 1;
	handle_var_set(env_list, key, value);
	*equal_sign = '=';
}

void	export_command(t_node *commandNode, t_env *env_list)
{
	if (!commandNode->left || !commandNode->left->value)
		env_command(env_list);
	else
		set_env_var(commandNode, &env_list);
}
