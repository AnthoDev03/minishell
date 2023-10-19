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

void	handle_var_set(char **env, char *key, char *value)
{
	int		len;
	char	**new_env;

	len = ft_strlen(key);
	while (*env)
	{
		if (ft_strncmp(*env, key, len) == 0 && (*env)[len] == '=')
		{
			replace_existing_var(env, key, value);
			return ;
		}
		env++;
	}
	if (!is_key_present(env, key, len))
	{
		new_env = add_new_env_var(env, key, value);
		env = new_env;
	}
}

void	set_env_var(t_node *commandNode, char **copyenv)
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
	handle_var_set(copyenv, key, value);
	*equal_sign = '=';
}

void	export_command(t_node *commandNode, char **env)
{
	if (!commandNode->left || !commandNode->left->value)
		env_command(env);
	else
		set_env_var(commandNode, env);
}
